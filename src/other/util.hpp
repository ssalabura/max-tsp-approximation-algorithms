#ifndef UTIL
#define UTIL

#include <boost/graph/adjacency_matrix.hpp>
#include <boost/graph/adjacency_list.hpp>
using namespace std;
using namespace boost;

typedef adjacency_matrix< undirectedS, no_property, property< edge_weight_t, int > > Graph;
typedef adjacency_list< vecS, vecS, undirectedS, no_property, property< edge_weight_t, int > > SparseGraph;

int weight(int u, int v, const Graph& g);

class TwoMatching {
    int n;
    const Graph& g;
    pair<int,int> *mate;
public:
    TwoMatching(const Graph& g);
    ~TwoMatching();
    void clear();
    void add(int u, int v);
    void add(pair<int, int> edge);
    void remove(int u, int v);
    void remove(pair<int,int> edge);
    bool contains(int u, int v);
    int weight_sum();
    pair<int,int> operator[](int i);
    TwoMatching& operator=(const TwoMatching& other);
};

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
    FindUnion& operator=(const FindUnion& other);
};

void select(const Graph& g, TwoMatching& C, TwoMatching& matching);
void finish(const Graph& g, TwoMatching& matching);
void optimize(const Graph& g, TwoMatching& matching);

#endif