/*
	COL 719 Assignment 1
	Author - Shreshth Tuli

	Determine if a circuit is combinational or sequential
*/

#include <iostream>
#include <vector>
#include <fstream>

#include <boost/graph/adjacency_list.hpp>

using namespace boost;

typedef boost::adjacency_list<
  boost::listS, boost::vecS,
  boost::directedS
  > Graph;

std::vector<int> adj;
int counter = 0;
bool cycle = false;

void dfs(Graph &graph, int v, int arrival[], int departure[])
{
	arrival[v-1] = counter++;
	adj.clear();

	Graph::out_edge_iterator eit, eend;
	std::tie(eit, eend) = boost::out_edges(v, graph);
	std::for_each(eit, eend, [&graph](Graph::edge_descriptor it)
	{ adj.push_back(boost::target(it, graph)); });

	std::vector<int> cp = adj;
	for (auto i = cp.begin(); i !=cp.end(); ++i){
		if(arrival[*i-1] == -1)
			dfs(graph, *i, arrival, departure);
		else if(departure[*i-1] == -1)
			cycle = true;      
	}

	departure[v-1] = counter++;      
} 

int main(int argc, char** argv){
	
	std::ifstream infile(argv[1]);

	int a, b, n;

	infile >> n;

	if(n==0){
		std::cout << "Combinational Circuit"; 
		return 0;
	}

	Graph g;

	while(infile >> a >> b)
		boost::add_edge(a, b, g);

	int *arrival = new int[n];
	int *departure = new int[n];

    for (int i = 0; i < n; i++){
        arrival[i] = -1;
        departure[i] = -1;
    }

	dfs(g, 1, arrival, departure);

	/*
	std::cout << std::endl;
	for (int i = 0; i < n; i++){
		std::cout << "arrival(" << i+1 << ") = " << arrival[i] << std::endl;
	}
		for (int i = 0; i < n; i++){
		std::cout << "departure(" << i+1 << ") = " << departure[i] << std::endl;
	}
	*/

	if(cycle)
		std::cout << "Sequential Circuit";
	else
		std::cout << "Combinational Circuit";

	return 0;
};