/*
 * ResourceManagerMaster.cpp
 *
 *  Created on: Oct 31, 2013
 *      Author: wangli
 */

#include "ResourceManagerMaster.h"
#include "../Environment.h"
ResourceManagerMaster::ResourceManagerMaster() {
	node_tracker_=NodeTracker::getInstance();
	logging_=new ResourceManagerMasterLogging();

	endpoint_=Environment::getInstance()->getEndPoint();
	framework=new Theron::Framework(*endpoint_);
	acter_=new ResourceManagerMasterActor(framework,this);
}

ResourceManagerMaster::~ResourceManagerMaster() {
	acter_->~ResourceManagerMasterActor();
	framework->~Framework();
	node_tracker_->~NodeTracker();
}
NodeID ResourceManagerMaster::RegisterNewSlave(NodeIP new_slave_ip_){
	NodeID new_node_id=node_tracker_->RegisterNode(new_slave_ip_);
	if(new_node_id==-1){
		/* Node with the given ip has already existed.*/
		logging_->elog("[%s] has already exists",new_slave_ip_.c_str());
		return false;
	}

//
//	if(node_to_resourceinfo_.find(new_node_id)!=node_to_resourceinfo_.end()){
//		/*The slaveId has already existed.*/
//		return false;
//	}
	node_to_resourceinfo_[new_node_id]=new ResourceInfo();

	logging_->log("[ip=%s, id=%d] is successfully registered.",new_slave_ip_.c_str(),new_node_id);

//	hashmap<NodeID,ResourceInfo*>::iterator it=node_to_resourceinfo_.begin();
//	while(it!=node_to_resourceinfo_.end()){
//		printf("%d-->  ",it->first);
//		it++;
//	}
//	printf("\n");

	return new_node_id;
}
std::vector<NodeID> ResourceManagerMaster::getSlaveIDList(){
	std::vector<NodeID> ret;
	boost::unordered_map<NodeID,ResourceInfo*>::iterator it=node_to_resourceinfo_.begin();
	while(it!=node_to_resourceinfo_.end()){
		ret.push_back(it->first);
		it++;
	}
	return ret;
}
bool ResourceManagerMaster::ApplyDiskBuget(NodeID target, unsigned size_in_mb){
	if(node_to_resourceinfo_.find(target)==node_to_resourceinfo_.cend()){
		/* target slave does not exist.*/
		return false;
	}
	if(node_to_resourceinfo_[target]->disk.take(size_in_mb))
		return true;
	return false;
}
bool ResourceManagerMaster::ApplyMemoryBuget(NodeID target, unsigned size_in_mb){
	if(node_to_resourceinfo_.find(target)==node_to_resourceinfo_.cend()){

		/* target slave does not exist.*/
		return false;
	}
	if(node_to_resourceinfo_[target]->memory.take(size_in_mb))
		return true;
	cout<<"no memory"<<endl;
	return false;
}
bool ResourceManagerMaster::RegisterDiskBuget(NodeID report_node_id, unsigned size_in_mb){
	if(node_to_resourceinfo_.find(report_node_id)==node_to_resourceinfo_.end()){
		/* target slave does not exists*/
		return false;
	}
	node_to_resourceinfo_[report_node_id]->disk.initialize(size_in_mb);
	logging_->log("Node(id=%d) reports its disk capacity=%d",report_node_id,size_in_mb);
	return true;
}
bool ResourceManagerMaster::RegisterMemoryBuget(NodeID report_node_id, unsigned size_in_mb){
	if(node_to_resourceinfo_.find(report_node_id)==node_to_resourceinfo_.end()){
		/* target slave does not exists*/
		return false;
	}
	node_to_resourceinfo_[report_node_id]->memory.initialize(size_in_mb);
	logging_->log("Node(id=%d) reports its memory capacity=%d",report_node_id,size_in_mb);
	return true;
}


ResourceManagerMaster::ResourceManagerMasterActor::ResourceManagerMasterActor(Theron::Framework* framework,ResourceManagerMaster* rmm)
:Theron::Actor(*framework,"ResourceManagerMaster"),rmm_(rmm){
	RegisterHandler(this,&ResourceManagerMasterActor::ReceiveStorageBudgetReport);
	RegisterHandler(this,&ResourceManagerMasterActor::ReceiveNewNodeRegister);
}

void ResourceManagerMaster::ResourceManagerMasterActor::ReceiveStorageBudgetReport(const StorageBudgetMessage &message,const Theron::Address from){
	if(!rmm_->RegisterDiskBuget(message.nodeid,message.disk_budget)){
		rmm_->logging_->elog("Fail to add the budget information to rmm!");
	}
	if(!rmm_->RegisterMemoryBuget(message.nodeid,message.memory_budget)){
		rmm_->logging_->elog("Fail to add the budget information to rmm!");
	}
//	rmm_->logging_->log("The storage of Slave[%d] has been registered, the disk=[%d]MB, memory=[%d]MB",message.nodeid,message.disk_budget,message.memory_budget);
	printf("The storage of Slave[%d] has been registered, the disk=[%d]MB, memory=[%d]MB",message.nodeid,message.disk_budget,message.memory_budget);
//	Send(0,from);
}
void ResourceManagerMaster::ResourceManagerMasterActor::ReceiveNewNodeRegister(const NodeRegisterMessage &message,const Theron::Address from){

	NodeID assigned_node_id=rmm_->RegisterNewSlave(message.get_ip());
	rmm_->logging_->log("Received register request from %s:%d, the allocated NodeID=%d",message.get_ip().c_str(),message.port,assigned_node_id);
	Send(assigned_node_id,from);
}
