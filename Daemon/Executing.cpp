/*
 * Executing.cpp
 *
 *  Created on: Feb 20, 2014
 *      Author: wangli
 */

#include "Executing.h"
Executing::Executing() {
	// TODO Auto-generated constructor stub

}

Executing::~Executing() {
	// TODO Auto-generated destructor stub
}

ResultSet* Executing::run_sql(std::string sql,std::string& error){
	/*
	 *  should call ExecuteLogicalQueryPlan. !!!!!!!!!!!!!!!!!!!!!!!!!!!!!! by yukai
	 * */

	//	char * test="select row_id,count(*) from cj where cj.row_id=1 group by cj.row_id;";
	ResultSet* resultset=0;
	Node* node=getparsetreeroot(sql.c_str());
	if(node==0){
		error="sql parser error!";
		return resultset;
	}
	LogicalOperator* plan=parsetree2logicalplan(node);
	if(plan==0){
		error="query optimization error!";
		return resultset;
	}

	plan->print();


	LogicalOperator* root=new LogicalQueryPlanRoot(0,plan,LogicalQueryPlanRoot::RESULTCOLLECTOR);
	//	unsigned long long int timer_start=curtick();

	BlockStreamIteratorBase* collector = root->getIteratorTree(
			1024 * 64 - sizeof(unsigned));
	collector->print();
	collector->open();
	collector->next(0);
	collector->close();
	resultset = collector->getResultSet();
	//	resultset->print();
	root->~LogicalOperator();;
	return resultset;
}

void Executing::run_sql(const std::string &sql, ResultSet *&result_set, bool &status, std::string &error_info, std::string &info, int fd){

	if (sql.length() <= 0) {
		status = false;
		result_set = NULL;
		error_info = "sql is NULL";
		return;
	}
	ExecuteLogicalQueryPlan(sql, result_set, status, error_info, info, fd);
	if(status==false) {
		cout<<"[ERROR] "<<error_info<<endl;
	}
	else {
//		if(result_set!=NULL)
//			result_set->print();
	}

}
