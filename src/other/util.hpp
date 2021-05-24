#ifndef UTIL
#define UTIL

#include <boost/graph/adjacency_matrix.hpp>
using namespace std;
using namespace boost;

typedef adjacency_matrix< undirectedS, no_property, property< edge_weight_t, int > > Graph;
typedef vector< pair<int,int> > TwoMatching;

class FindUnion {
    int n;
    int *parent;
    int *rank;
    int *d;
    int edges_count;
public:
    FindUnion(int n);
    ~FindUnion();
    int Find(int v);
    void Union(int u, int v);
    bool canUnion(int u, int v);
};

void select(const Graph& g, TwoMatching& matching);
void finish(const Graph& g, TwoMatching& matching);
void optimize(const Graph& g, TwoMatching& matching);

int weight(int u, int v, const Graph& g);

void matching_empty(int n, TwoMatching& matching);
void matching_add(int u, int v, TwoMatching& matching);
void matching_remove(int u, int v, TwoMatching& matching);
bool in_matching(int u, int v, TwoMatching& matching);
int matching_weight(const Graph& g, TwoMatching& matching);

#endif