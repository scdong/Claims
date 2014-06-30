/*
 * Sort.h
 *
 *  Created on: 2014-3-1
 *      Author: casa
 */

#ifndef LOGICALSORT_H_
#define LOGICALSORT_H_

#include "../LogicalQueryPlan/LogicalOperator.h"
#include "../Scheduler/Dataflow.h"
#include "../Catalog/Catalog.h"
#include "../BlockStreamIterator/BlockStreamIteratorBase.h"
#include "../BlockStreamIterator/ParallelBlockStreamIterator/BlockStreamSortIterator.h"
#include<vector>
#include<string.h>
#include<iostream>
class LogicalSort: public LogicalOperator{
public:
	struct OrderByAttr{
//		const char *tbl_;
//		const char *attr_;
		const char *ta_;
		OrderByAttr(const char *t,const char *a){
	///		tbl_=t;attr_=a;
		}
		OrderByAttr(const char *ta){
			ta_=ta;
	//		printf("ta=%x len=%d ta_=%x len=%d\n",ta,strlen(ta),ta_,strlen(ta_));
		//	cout<<"order by att str ta=  "<<ta<<" @@@ta_= "<<ta_<<endl;
		}
	};

	LogicalSort(LogicalOperator *child, vector<LogicalSort::OrderByAttr*>oba);
	virtual ~LogicalSort();

	Dataflow getDataflow();
	BlockStreamIteratorBase *getIteratorTree(const unsigned& blocksize);

	int getOrderByKey(const char *,const char *);
	int getOrderByKey(const char *);

	void printOrderByAttr()const;
	void print(int level=0)const;
	virtual bool GetOptimalPhysicalPlan(Requirement requirement,PhysicalPlanDescriptor& physical_plan_descriptor, const unsigned & block_size=4096*1024){};

private:
	vector<OrderByAttr*> oba_;
	Dataflow dataflow_;
	LogicalOperator *child_;
};

#endif /* SORT_H_ */
