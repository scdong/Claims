/*
 * test_csb_index.cpp
 *
 *  Created on: Feb 10, 2015
 *      Author: scdong
 */

#include <iostream>
#include "../CSBTree.h"
using namespace std;

static int test_csb_index()
{
	data_original* data = new data_original [50];
	for (unsigned i = 0; i < 50; i++)
	{
		data[i]._key = i*2;
		data[i]._block_off = 0;
		data[i]._tuple_off = i;
	}
	CSBTree* csb_tree = new CSBTree();
	csb_tree->BulkLoad(data, 50);
	csb_tree->printTree();
	return 0;
}
