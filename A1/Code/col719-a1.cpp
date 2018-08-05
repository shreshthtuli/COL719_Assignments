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

typedef boost::adjacency_list<
  boost::listS, boost::vecS,
  boost::directedS
  > Graph;

typedef boost::graph_traits<Graph>::vertex_descriptor vertex_t;

std::deque<vertex_t> topologicalSorted;

void topologicalSort(Graph &graph)
{
    try{
        boost::topological_sort(graph, front_inserter(topologicalSorted));
    }
    catch (boost::not_a_dag){
        std::cout << "Sequential Circuit\n";
        return;
    }

    std::cout << "Combinational Circuit\n";
} 

int main(){

	std::ifstream infile("input.txt");
	int a, b, n;

	infile >> n;

	Graph g;

	while(infile >> a >> b)
		boost::add_edge(a, b, g);

	topologicalSort(g);

	return 0;
};