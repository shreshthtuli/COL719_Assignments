
#include <iostream>
#include <boost/graph/adjacency_list.hpp>

using namespace boost;
using namespace std;

int main()
{
/*********************** Graph creation *********************************/
  int N,a,b,j;
  cout << "Enter number of nodes: "<<endl;
  cin >> N;
  j = N;
  // Declares a graph g
  adjacency_list <> g;
  // Adding vertices to graph g
  while(j){
    add_vertex(g);
    j--;
  }


  while(1)
  {
	cout <<"Connect Nodes (x->y) : ";
	cin >> a >> b;
	if( a < 0 || b < 0){
		cout << "Your Graph is ready\n"<< endl;
		break;
	}
	else if(a < N || b < N) {
		cout << "Connected: (" << a << "->" << b <<")"<< endl;
		add_edge(a, b, g);
	}
  }

/**************************** Print neighbors of each vertex *****************************/

  graph_traits < adjacency_list <> >::vertex_iterator i, eend;
  graph_traits < adjacency_list <> >::adjacency_iterator ai, a_end;	// out_edge_iterator can also be used to get the list of adjacency vertices

// A PropertyGraph is a graph that has some property associated with each of the vertices or edges in the graph.
//
// vertex_index_t is the type of property which is being accessed. 'vertex_index' is one of its value. 
// Eg. enum vertex_index_t
//     {
//	 vertex_index
//     }
// (https://www.boost.org/doc/libs/1_60_0/libs/graph/doc/property.html)
//
// get(vertex_index, g) returns the property map with the property of type vertex_index

  property_map < adjacency_list <>, vertex_index_t >::type index_map = get(vertex_index, g);

    for (tie(i, eend) = vertices(g); i != eend; i++) {
    cout << "Neighbors of vertex " << (int)get(index_map, *i) << " ==> ";		
        for (tie(ai, a_end) = adjacent_vertices(*i, g); ai != a_end; ai++) { 
            cout << (int)get(index_map, *ai) << "  ";
        }
    cout << endl;
    }
}


