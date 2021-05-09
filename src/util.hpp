#include <iostream>
#include <algorithm>
#include <boost/graph/adjacency_matrix.hpp>
#include <boost/graph/maximum_weighted_matching.hpp>
using namespace std;
using namespace boost;

typedef adjacency_matrix< undirectedS, no_property, property< edge_weight_t, int > > Graph;
typedef vector< pair<int,int> > TwoMatching;

void select(const Graph& g, TwoMatching& matching);
void finish(const Graph& g, TwoMatching& matching);
void optimize(const Graph& g, TwoMatching& matching);

int weight(int u, int v, const Graph& g);

bool in_matching(int u, int v, TwoMatching& matching);
void matching_add(int u, int v, TwoMatching& matching);
void matching_remove(int u, int v, TwoMatching& matching);
int matching_weight(const Graph& g, TwoMatching& matching);