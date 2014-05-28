/*
 * BlockStreamJoinIterator.h
 *
 *  Created on: 2013-8-27
 *      Author: casa
 */

#ifndef BLOCKSTREAMJOINITERATOR_H_
#define BLOCKSTREAMJOINITERATOR_H_

#include "../BlockStreamIteratorBase.h"
#include "../ExpandableBlockStreamIteratorBase.h"
#include "../../Debug.h"
#include "../../utility/rdtsc.h"
#include "../../common/hash.h"
#include "../../common/hashtable.h"

#include <iostream>
#include <vector>
#include <map>
#include <list>
using namespace std;

class BlockStreamJoinIterator:public ExpandableBlockStreamIteratorBase{
public:
	class join_thread_context:public thread_context{
	public:
		BlockStreamBase* block_for_asking_;
		BlockStreamBase::BlockStreamTraverseIterator* block_stream_iterator_;
		BasicHashTable::Iterator hashtable_iterator_;
	};
	struct remaining_block{
		remaining_block(BlockStreamBase *bsb_right,BlockStreamBase::BlockStreamTraverseIterator *bsti)
		:bsb_right_(bsb_right),blockstream_iterator(bsti){};
		remaining_block():bsb_right_(0),blockstream_iterator(0){};
		remaining_block(const remaining_block&r){
			bsb_right_=r.bsb_right_;
			blockstream_iterator=r.blockstream_iterator;
			hashtable_iterator_=r.hashtable_iterator_;
		}
		BlockStreamBase *bsb_right_;
		BlockStreamBase::BlockStreamTraverseIterator *blockstream_iterator;
		BasicHashTable::Iterator hashtable_iterator_;
	};

	class State{
		friend class BlockStreamJoinIterator;
	public:
		State(BlockStreamIteratorBase *child_left,
				       BlockStreamIteratorBase *child_right,
				       Schema *input_schema_left,
				       Schema *input_schema_right,
				       Schema *output_schema,
				       Schema *ht_schema,
				       std::vector<unsigned> joinIndex_left,
				       std::vector<unsigned> joinIndex_right,
				       std::vector<unsigned> payload_left,
				       std::vector<unsigned> payload_right,
				       unsigned ht_nbuckets,
				       unsigned ht_bucketsize,
				       unsigned block_size);

		State(){};
		friend class boost::serialization::access;
		template<class Archive>
		void serialize(Archive & ar, const unsigned int version){
			ar & child_left & child_right & input_schema_left & input_schema_right & output_schema & ht_schema & joinIndex_left & joinIndex_right & payload_left & payload_right
			& ht_nbuckets & ht_bucketsize & block_size_;
		}
	public:
		//input and output
		BlockStreamIteratorBase *child_left,*child_right;
		Schema *input_schema_left,*input_schema_right;
		Schema *output_schema,*ht_schema;

		//how to join
		std::vector<unsigned> joinIndex_left;
		std::vector<unsigned> joinIndex_right;
		std::vector<unsigned> payload_left;
		std::vector<unsigned> payload_right;

		//hashtable
		unsigned ht_nbuckets;
		unsigned ht_bucketsize;

		unsigned block_size_;
	};
	BlockStreamJoinIterator(State state);
	BlockStreamJoinIterator();
	virtual ~BlockStreamJoinIterator();

	bool open(const PartitionOffset& partition_offset=0);
	bool next(BlockStreamBase *block);
	bool close();
	void print();
private:
	bool atomicPopRemainingBlock(remaining_block & rb);
	void atomicPushRemainingBlock(remaining_block rb);
	BlockStreamBase* AtomicPopFreeBlockStream();
	void AtomicPushFreeBlockStream(BlockStreamBase* block);
	BlockStreamBase* AtomicPopFreeHtBlockStream();
	void AtomicPushFreeHtBlockStream(BlockStreamBase* block);
private:
	State state_;
	/* joinIndex map to the output*/
	std::map<unsigned,unsigned> joinIndex_left_to_output;
	/* payload_left map to the output*/
	std::map<unsigned,unsigned> payload_left_to_output;
	/* payload_right map to the output*/
	std::map<unsigned,unsigned> payload_right_to_output;

	PartitionFunction *hash;
	BasicHashTable *hashtable;
	Schema *ht_schema;

	std::list<remaining_block> remaining_block_list_;
	std::list<BlockStreamBase *> free_block_stream_list_;
	std::list<BlockStreamBase *> ht_free_block_stream_list_;

//	semaphore sema_open_;
//	volatile bool open_finished_;
	unsigned reached_end;
	Lock lock_;
//	Barrier barrier_;

	//debug
	unsigned produced_tuples;
	unsigned consumed_tuples_from_right;
	unsigned consumed_tuples_from_left;
	unsigned tuples_in_hashtable;
	unsigned water_mark;

#ifdef TIME
	unsigned long long timer;
#endif

    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version){
            ar & boost::serialization::base_object<ExpandableBlockStreamIteratorBase>(*this) & state_;
    }
};

#endif /* BLOCKSTREAMJOINITERATOR_H_ */
