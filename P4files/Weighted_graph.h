/*****************************************
 * Instructions
 *  - Replace 'uwuserid' with your uWaterloo User ID
 *  - Select the current calendar term and enter the year
 *  - List students with whom you had discussions and who helped you
 *
 * uWaterloo User ID:  s276shar@uwaterloo.ca
 * Submitted for ECE 250
 * Department of Electrical and Computer Engineering
 * University of Waterloo
 * Calender Term of Submission:  Fall 2016
 *
 * By submitting this file, I affirm that
 * I am the author of all modifications to
 * the provided code.
 *
 * The following is a list of uWaterloo User IDs of those students
 * I had discussions with in preparing this project:
 *    - 
 *
 * The following is a list of uWaterloo User IDs of those students
 * who helped me with this project (describe their help; e.g., debugging):
 *    -
 *****************************************/

#ifndef WEIGHTED_GRAPH_H
#define WEIGHTED_GRAPH_H

#ifndef nullptr
#define nullptr 0
#endif

#include <iostream>
#include <limits>
#include "Exception.h"
#include "Disjoint_sets.h"

using namespace std;

struct edge{
	double weight;
	int first;
	int second;
};

class Weighted_graph {
	private:
		static const double INF;
		double** graph_matrix;
		int num_nodes;
		int num_edges;
		// Do not implement these functions!
		// By making these private and not implementing them, any attempt
		// to make copies or assignments will result in errors
		Weighted_graph( Weighted_graph const & );
		Weighted_graph &operator=( Weighted_graph );

		// your choice

	public:
		Weighted_graph( int = 10 );
		~Weighted_graph();

		int degree( int ) const;
		int edge_count() const;
		std::pair<double, int> minimum_spanning_tree() const;

		bool insert_edge( int, int, double );
		bool erase_edge( int, int );
		void clear_edges();

	// Friends

	friend std::ostream &operator<<( std::ostream &, Weighted_graph const & );
};

const double Weighted_graph::INF = std::numeric_limits<double>::infinity();

Weighted_graph::Weighted_graph(int n ) {
	if (n < 0){
		throw illegal_argument();
	}
	int i = 0;
	int j = 0;
	num_nodes = n;
	num_edges = 0;
	graph_matrix = new double*[num_nodes];
	for(int i = 0; i < num_nodes; ++i){
    	graph_matrix[i] = new double[num_nodes];
	}
	for (int i = 0; i < num_nodes; ++i){
		for (int j = 0; j < num_nodes; ++j){
			graph_matrix[i][j] = INF;
		}
	}
}

Weighted_graph::~Weighted_graph() {
	int i=0;
	while (i < num_nodes){
	 	delete[] graph_matrix[i];
	 	i++;
	}
	delete[] graph_matrix; 
}

int Weighted_graph::degree(int u) const {
	if(u < 0 || u > num_nodes){
		throw illegal_argument();
	}
	int degree = 0;
	for(int i = 0; i < num_nodes; ++i){
		if(graph_matrix[u][i]!= INF){
			degree++;
		}
	}
	return degree;
}

int Weighted_graph::edge_count() const {
	return num_edges;
}

bool Weighted_graph::erase_edge(int i, int j) {
	if(i >= num_nodes || i < 0 || j >= num_nodes || j < 0){
		throw illegal_argument();
	}
	if(i == j){
		return true;
	}
	else if(graph_matrix[i][j] == INF){
		return false;
	}
	else if(graph_matrix[i][j] != INF && graph_matrix[j][i] != INF){
		graph_matrix[i][j] = INF;
		graph_matrix[j][i] = INF;
		num_edges--;
		return true;
	}
}

void Weighted_graph::clear_edges() {
	for (int i = 0; i < num_nodes; i++){
		for (int j = 0; j < num_nodes; j++){
			graph_matrix[i][j] = 0;
		}
	}
	num_edges = 0;
}

bool Weighted_graph::insert_edge( int i, int j, double d ) {
	if(i > num_nodes-1 || i < 0 || j > num_nodes-1 || j < 0 || d <= 0){
		throw illegal_argument();
	}
	else if(i == j){
		return false;
	}
	else if(graph_matrix[i][j] == INF){	
		graph_matrix[i][j] = d;
		graph_matrix[j][i] = d;
		num_edges++;
		return true;
	}
	else if (graph_matrix[i][j] != INF){
		graph_matrix[i][j] = d;
		graph_matrix[j][i] = d;
		return true;		
	}
}

// void bubbleSort(edge *a, int n)
// {	
// 	for(int i=1;i<n;i++){
//         for(int j=0;j<n;j++){
//         	if(a[j].weight>a[j+1].weight){
//              	int temp1 = a[i].first;
// 				int temp2 = a[i].second;
// 				double tempweightfirst = a[i].weight;

// 				a[i].first = a[j].first;
// 				a[i].second = a[j].second;
// 				a[i].weight = a[j].weight;

// 				a[j].first = temp1;
// 				a[j].second = temp2;
// 				a[j].weight = tempweightfirst;

//             }
//         }
//     }
// }

std::pair<double, int> Weighted_graph::minimum_spanning_tree() const {
// //First, sort the edges in non-decreasing order
// //using make set, we create as many sets as # of vertices
// //pick one edge at a time and check if they are both in the same disjoint set
	//if same disjoint, ignore the set
	//if different disjoint, merge disjoint sets into 1 and put edge into final result

Disjoint_set disjoint(num_nodes);
double totalweight = 0.0;
int flaggedEdges = 0;
int counter = 0;

edge *edges = new edge[num_edges];

for(int i = 0; i <= num_nodes-1; i++){
	for(int j = i+1; j<= num_nodes-1;j++){
		if(graph_matrix[i][j] != INF){
			edges[counter].first = i;
			edges[counter].second = j;
			edges[counter].weight = graph_matrix[i][j];
			counter++;
		}
	}
}

for (int i=0; i<counter; i++){
	for( int j=i+1; j<counter; j++){
		if(edges[i].weight>edges[j].weight){
			int temp1 = edges[i].first;
			int temp2 = edges[i].second;
			double tempweightfirst = edges[i].weight;

			edges[i].first = edges[j].first;
			edges[i].second = edges[j].second;
			edges[i].weight = edges[j].weight;

			edges[j].first = temp1;
			edges[j].second = temp2;
			edges[j].weight = tempweightfirst;
		}
	}
}

	for(int i=0; i<=num_edges-1; ++i) {
		if(disjoint.find_set(edges[i].first) != disjoint.find_set(edges[i].second)) {
			disjoint.union_sets(edges[i].first, edges[i].second);
						totalweight += edges[i].weight;
		}
		flaggedEdges++;
		if(disjoint.num_sets() == 1){
				break;
		}
	}
	delete[] edges;
	return std::pair<double, int>(totalweight, flaggedEdges);
}

// cout<<"works";	

// Disjoint_set disjoint(num_nodes);
// int edges_flagged = 0;
// double totalweight = 0;
// int counter = 0;
// edge *edges = new edge[num_edges];

// for(int i = 0; i < num_nodes; i++){
// 	for(int j = i+1; j< num_nodes;j++){
// 		if(graph_matrix[i][j] != INF){
// 			cout <<" llama ";
// 			edges[counter].first = i;
// 			edges[counter].second = j;
// 			edges[counter].weight = graph_matrix[i][j];
// 			counter++;
// 		}
// 	}
// }

// cout<<" welldone ";

// for (int i=0; i<num_edges; i++){
// 	cout<<"massive";
// 	for( int j=i+1; j<num_edges; j++){
// 		cout<<"liquid";
// 		if(edges[i].weight>edges[j].weight){
// 			cout<<"penis";
// 			int temp1 = edges[i].first;
// 			int temp2 = edges[i].second;
// 			double tempweightfirst = edges[i].weight;

// 			edges[i].first = edges[j].first;
// 			edges[i].second = edges[j].second;
// 			edges[i].weight = edges[j].weight;

// 			edges[j].first = temp1;
// 			edges[j].second = temp2;
// 			edges[j].weight = tempweightfirst;
// 		}
// 	}
// }

// for(int i=0; i<=num_edges-1; ++i) {
// 	cout<<"shrey";
// 	if(disjoint.num_sets() == 1){
// 		cout<<"assface";
// 		break;
// 	}
// 	if(disjoint.find_set(edges[i].first) != disjoint.find_set(edges[i].second)) {
// 		cout<<"ashley";
// 		disjoint.union_sets(edges[i].first, edges[i].second);
// 		totalweight += edges[i].weight;
// 	}	

// 	edges_flagged++;
// 	}
// 	return std::pair<double, int>( totalweight, edges_flagged );

// std::pair<double, int> Weighted_graph::minimum_spanning_tree() const {

// }

std::ostream &operator<<( std::ostream &out, Weighted_graph const &graph ) {
	
	return out;
}


#endif