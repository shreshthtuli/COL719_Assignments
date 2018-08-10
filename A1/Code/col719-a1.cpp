/*
	COL 719 Assignment 1
	Author - Shreshth Tuli

	Determine if a circuit is combinational or sequential
*/

#include <iostream>
#include <vector>
#include <fstream>
#include <deque>

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/topological_sort.hpp>

using namespace boost;
using namespace std;

typedef adjacency_list<listS, vecS, directedS> Graph;
typedef graph_traits<Graph>::vertex_descriptor vertex_t;

deque<vertex_t> topologicalSorted;

void topologicalSort(Graph &graph)
{
    try{
        topological_sort(graph, front_inserter(topologicalSorted));
    }
    catch (not_a_dag){
        cout << "Sequential Circuit\n"; return;
    }

    std::cout << "Combinational Circuit\n";
} 

int main(int argc, char** argv){
	
	ifstream infile(argv[1]);

	int a, b, n;
	infile >> n;

	if(n==0){
		cout << "Combinational Circuit"; 
		return 0;
	}

	Graph g;

	while(infile >> a >> b)
		add_edge(a, b, g);

	topologicalSort(g);
	return 0;
};