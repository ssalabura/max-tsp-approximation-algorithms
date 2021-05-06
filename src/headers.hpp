#include <iostream>
#include <algorithm>
#include <boost/graph/adjacency_matrix.hpp>
#include <boost/graph/maximum_weighted_matching.hpp>
using namespace std;
using namespace boost;

typedef adjacency_matrix< undirectedS, no_property, property< edge_weight_t, int > > Graph;

int weight(int u, int v, const Graph& g) {
    return get(edge_weight, g, edge(u,v,g).first);
}