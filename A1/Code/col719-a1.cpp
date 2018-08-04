#include <iostream>
#include <vector>
#include <fstream>

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/breadth_first_search.hpp>

typedef boost::adjacency_list<
  boost::listS, boost::vecS,
  boost::directedS
  > Graph;

using namespace boost;

bool cycle(Graph &G, int u, int v){

  std::vector<int> distances(num_vertices(G), 0);

  breadth_first_search(G, vertex(u, G),
               visitor(make_bfs_visitor(record_distances(&distances[0], on_tree_edge())))); 

  if(distances[v] != 0)
    return true;
  return false;
};

int main(){

	std::ifstream infile("input.txt");
	int a, b, n;

	infile >> n;

	Graph g;

	while(infile >> a >> b){
		//std::cout << "Edge : " << a << "," << b << std::endl;
		if(num_vertices(g) > 1 && cycle(g, a, b)){
			std::cout << "Sequential circuit";
			return 0;
		}
		boost::add_edge(a, b, g);
	}

	std::cout << "Combinational Circuit";
	return 0;
};