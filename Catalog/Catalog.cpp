/*
 * Catalog.cpp
 *
 *  Created on: Oct 31, 2013
 *      Author: wangli
 */

#include "Catalog.h"
Catalog* Catalog::instance_=0;
Catalog::Catalog() {
	logging=new CatalogLogging();
	binding_=new ProjectionBinding();
}

Catalog::~Catalog() {
	logging->~Logging();
	binding_->~ProjectionBinding();
}
Catalog* Catalog::getInstance(){
	if(instance_==0){
		instance_=new Catalog();
	}
	return instance_;
}
unsigned Catalog::allocate_unique_table_id(){
	return table_id_allocator.allocate_unique_table_id();
}
bool Catalog::add_table(TableDescriptor* const &table){
	std::string new_table_name=table->getTableName();
	TableID new_table_id=table->get_table_id();
	boost::unordered_map<std::string,TableDescriptor*>::iterator it_name_to_table=name_to_table.find(new_table_name);
	if(it_name_to_table!=name_to_table.end()){
		return false;
	}
	boost::unordered_map<TableID,TableDescriptor*>::iterator it_tableid_to_table=tableid_to_table.find(new_table_id);
	if(it_tableid_to_table!=tableid_to_table.find(new_table_id)){
		return false;
	}
	/*The check is successful. Now we can add the new table into the catalog module.*/
	name_to_table[new_table_name]=table;
	tableid_to_table[new_table_id]=table;
	logging->log("New table \"%s\",id=%d is created!",new_table_name.c_str(),new_table_id);

	return true;
}
TableDescriptor* Catalog::getTable(const TableID &target)const{
	if(tableid_to_table.find(target)==tableid_to_table.cend())
		return NULL;

	/* at could retain const while [] doesn't.*/
	return tableid_to_table.at(target);

}
TableDescriptor* Catalog::getTable(const std::string& table_name) const{
	if(name_to_table.find(table_name)==name_to_table.cend())
		return NULL;

	/* at could retain const while [] doesn't.*/
	return name_to_table.at(table_name);
}
ProjectionDescriptor* Catalog::getProjection(const ProjectionID& pid) const{
	const TableDescriptor* td=getTable(pid.table_id);
	return td==0?0:td->getProjectoin(pid.projection_off);
}
ProjectionBinding* Catalog::getBindingModele()const{
	return binding_;
}

bool Catalog::isAttributeExist(const std::string& table_name,const std::string& attribute_name )const{
	TableDescriptor* td=getTable(table_name);
	if(td==0){
		return false;
	}
	else
		return td->isExist(attribute_name);
}

vector<PartitionID> Catalog::getPartitionIDList(const std::string& table_name, const std::string& attribute_name)
{
	vector<PartitionID> ret;
	ret.clear();
	TableDescriptor* table_descripter = this->getTable(table_name);
	ProjectionDescriptor* projection_descripter = NULL;
	unsigned projection_num = table_descripter->getNumberOfProjection();
	for (unsigned i = 0; i < projection_num; i++)
	{
		projection_descripter = table_descripter->getProjectoin(i);
		if (projection_descripter->isExist(attribute_name))
			break;
	}
	return projection_descripter->getPartitioner()->getPartitionIDList();
}
