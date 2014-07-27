/*
 * BlockStreamProjectIterator.cpp
 *
 *  Created on: 2014-2-17
 *      Author: casa
 */

#include "BlockStreamProjectIterator.h"

BlockStreamProjectIterator::BlockStreamProjectIterator() {
	sema_open_.set_value(1);
	open_finished_=false;
}

BlockStreamProjectIterator::~BlockStreamProjectIterator() {

}

BlockStreamProjectIterator::BlockStreamProjectIterator(State state)
:state_(state){
	sema_open_.set_value(1);
	open_finished_=false;
}

BlockStreamProjectIterator::State::State(Schema * input, Schema* output, BlockStreamIteratorBase * children, unsigned blocksize, Mapping map, vector<ExpressItem_List> v_ei)
:input_(input),output_(output),children_(children),block_size_(blocksize),map_(map),v_ei_(v_ei){

}

bool BlockStreamProjectIterator::open(const PartitionOffset& partition_offset){
	state_.children_->open(partition_offset);
	if(sema_open_.try_wait()){
		BlockStreamBase *bsb=new BlockStreamFix(64*1024-sizeof(unsigned),state_.input_->getTupleMaxSize());
		free_block_stream_list_.push_back(bsb);
		open_finished_=true;
	}
	else
	{
		while (!open_finished_)
			usleep(1);
	}
	return true;
}

/*
 * now the expressions computing speed is slow because of the copy between among the expressions
 * todo: seek the pointer of data and LLVM will be solved by wangli.
 * */
bool BlockStreamProjectIterator::next(BlockStreamBase *block){
	unsigned total_length_=state_.output_->getTupleMaxSize();
//	void *tuple=0;
//	void *column_in_combinedTuple=0;
	/* tuple to include the max tuple! */
//	void *combinedTuple_=memalign(cacheline_size,state_.output_->getTupleMaxSize());;
//	void *cur=0;

	remaining_block rb;
	if(atomicPopRemainingBlock(rb)){
		while(1){
			void *cur=0;
			void *tuple=0;
			if((cur=rb.bsti_->currentTuple())==0){
				rb.bsb_->setEmpty();
				/* get a block from downstreams */
				if(state_.children_->next(rb.bsb_)==false){
					/* if downstreams has no data and block is not empty, return true */
					if(!block->Empty()){
						atomicPushRemainingBlock(rb);
						return true;
					}
					return false;
				}
				/* if downstreams has data, reset the cur */
				rb.bsti_->reset();
				cur=rb.bsti_->currentTuple();
			}

			if((tuple=block->allocateTuple(total_length_))>0){
				for(unsigned i=0;i<state_.v_ei_.size();i++){
					ExpressionItem result;
					ExpressItem_List toCalc;
					int variable_=0;
					for(unsigned j=0;j<state_.v_ei_[i].size();j++){
						ExpressionItem ei;
						if(state_.v_ei_[i][j].type==ExpressionItem::variable_type){
							int nth=state_.map_.atomicPopExpressionMapping(i).at(variable_); //n-th column in tuple
							ei.setValue(state_.input_->getColumnAddess(nth,cur),state_.input_->getcolumn(nth).type);
							variable_++;
						}
						else if(state_.v_ei_[i][j].type==ExpressionItem::const_type){
							ei.return_type=state_.v_ei_[i][j].return_type;
							ei.setData(state_.v_ei_[i][j].content.data);
						}
						else{
							ei.setOperator(state_.v_ei_[i][j].getOperatorName().c_str());
						}
						toCalc.push_back(ei);
					}
					ExpressionCalculator::calcuate(toCalc,result);
					copyColumn(tuple,result,state_.output_->getcolumn(i).get_length());
					tuple=(char *)tuple+state_.output_->getcolumn(i).get_length();
				}
				rb.bsti_->increase_cur_();
			}
			else{
				atomicPushRemainingBlock(rb);
				return true;
			}
		}
	}

	lock_.acquire();
	BlockStreamBase * v_bsb;
	if(!free_block_stream_list_.empty()){
		v_bsb=free_block_stream_list_.front();
		free_block_stream_list_.pop_front();
	}
	else{
		return false;
	}
	lock_.release();

	v_bsb->setEmpty();
	BlockStreamBase::BlockStreamTraverseIterator* traverse_iterator=v_bsb->createIterator();
	traverse_iterator->reset();
	atomicPushRemainingBlock(remaining_block(v_bsb,traverse_iterator));
	return next(block);
}

bool BlockStreamProjectIterator::close(){
	sema_open_.post();
	open_finished_ =false;
	free_block_stream_list_.clear();
	remaining_block_list_.clear();
	return state_.children_->close();
}


bool BlockStreamProjectIterator::atomicPopRemainingBlock(remaining_block & rb){
	lock_.acquire();
	if(remaining_block_list_.size()>0){
		rb=remaining_block_list_.front();
		remaining_block_list_.pop_front();
		lock_.release();
		return true;
	}
	else{
		lock_.release();
		return false;
	}
}

void BlockStreamProjectIterator::atomicPushRemainingBlock(remaining_block rb){
	lock_.acquire();
	remaining_block_list_.push_back(rb);
	lock_.release();
}

bool BlockStreamProjectIterator::copyColumn(void *&tuple,ExpressionItem &result,int length){
	switch(result.return_type){
		case t_int:{
			memcpy(tuple,&result.content.data.value._int,length);
			break;
		}
		case t_float:{
			memcpy(tuple,&result.content.data.value._float,length);
			break;
		}
		case t_u_long:{
			memcpy(tuple,&result.content.data.value._ulong,length);
			break;
		}
		case t_string:{
			memcpy(tuple,result._string.c_str(),length);
			break;
		}
		case t_decimal:{
			memcpy(tuple,&result._decimal,length);
			break;
		}
		case t_date:{
			memcpy(tuple,&result._date,length);
			break;
		}
		case t_time:{
			memcpy(tuple,&result._time,length);
			break;
		}
		case t_datetime:{
			memcpy(tuple,&result._datetime,length);
			break;
		}
		case t_double:{
			memcpy(tuple,&result.content.data.value._double,length);
			break;
		}
		case t_smallInt:{
			memcpy(tuple,&result.content.data.value._sint,length);
			break;
		}
		default:{
			cout<<"missing the operator!!!"<<endl;
			break;
		}
	}
}
void BlockStreamProjectIterator::print()
{
	cout<<"proj: NULL"<<endl;
			state_.children_->print();

}
