	
#ifndef DISJOINT_SET_H
#define DISJOINT_SET_H

#ifndef nullptr
#define nullptr 0
#endif


#include <limits>
#include "Exception.h"

using namespace std;

struct ll_entry; // represents each element of the linked list
struct set_info; // keeps track of the information (pointers to head and tail and the size of the set) of each set
//could we delete the above two lines?


struct ll_entry{ 
	int content;
	set_info* ptr_to_info; // ptr to the info entry of the corresponding set
	ll_entry* next;
	
};

struct set_info { 
	ll_entry* head;
	ll_entry* tail;
	int size;
};

class Disjoint_set {

private:
	ll_entry** nodes;
	set_info** sets;
	int set_counter;
	int initial_num_sets;
public:
	Disjoint_set(int);
	~Disjoint_set();
	int find_set(int) const;
	int num_sets() const;
	void union_sets(int, int);
};

Disjoint_set::Disjoint_set(int n) : nodes(new ll_entry*[n]), 
sets (new set_info*[n]), 
set_counter(n),
initial_num_sets(n) {
	int i = 0;
	for(i = 0; i < n; i++){
		sets[i] =  new set_info();
		nodes[i] = new ll_entry();

		sets[i]->size = 1;
		sets[i]->head = nodes[i];
		sets[i]->tail = nodes[i];

		nodes[i]->content = i;
		nodes[i]->ptr_to_info = sets[i];
		nodes[i]->next = nullptr;	
	}
}

Disjoint_set::~Disjoint_set() {
	int i=0;
	int j=0;
	while(i < initial_num_sets){
		delete nodes[i];
		i++;
	}
	
	while(j < initial_num_sets){
			delete sets[j];
		j++;
	}
	delete[] nodes;
	delete[] sets;
}
int Disjoint_set::find_set(int item) const{
	return nodes[item]->ptr_to_info->head->content;
}

int Disjoint_set::num_sets() const {
	return set_counter;
}

void Disjoint_set::union_sets(int node_index1, int node_index2) {
	if (node_index1 == node_index2)
		return;
	
	set_info* si1 = nodes[node_index1]->ptr_to_info;
	set_info* si2 = nodes[node_index2]->ptr_to_info;

	// ni1: the index of the larger set, ni2: the index of the smaller index
	int ni1 = si1->size >= si2->size ? node_index1 : node_index2; 
	int ni2 = si1->size < si2->size ? node_index1 : node_index2;

	/* iterate through the shorter list and modify the pointers
	while (has not reached the end of set) {
		....
	}*/

	nodes[ni1]->ptr_to_info->size += nodes[ni2]->ptr_to_info->size; //changing the size accordingly
	nodes[ni1]->ptr_to_info->tail->next = nodes[ni2]->ptr_to_info->head; //making sure its in the same set
	nodes[ni1]->ptr_to_info->tail = nodes[ni2]->ptr_to_info->tail; //since same, the got same tail

	ll_entry* pointer = nodes[ni2]->ptr_to_info->head;
	//int limit = pointer->ptr_to_info->size;

	while(pointer!=nullptr){
		pointer->ptr_to_info = nodes[ni1]->ptr_to_info;
		pointer=pointer->next;
		//limit--;
	}
	// do we need to modify anything else?

	// delete the set_info entry that no longer exists
	set_counter--;
}


#endif