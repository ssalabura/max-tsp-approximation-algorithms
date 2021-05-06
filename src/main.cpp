#include <iostream>
#include <boost/graph/adjacency_matrix.hpp>
using namespace std;
using namespace boost;

typedef adjacency_matrix< undirectedS, no_property, property< edge_weight_t, int > > Graph;

int maxtsp(const Graph& g);

int main() {
    int n;
    cin >> n;
    Graph g(n);

    int w;
    for(int i=0; i<n; i++) {
        for(int j=i+1; j<n; j++) {
            cin >> w;
            add_edge(i,j,w,g);
        }
    }
    cout << maxtsp(g);
}