#include "util.hpp"
#include "maximum_weighted_2_matching.hpp"
#include <boost/graph/maximum_weighted_matching.hpp>

void select(const Graph& g, TwoMatching& matching) {
    int n = num_vertices(g);
    bool *visited = new bool[n]();
    FindUnion fu(n);
    TwoMatching C(g), W(g);

    maximum_weighted_2_matching(g, C);
    vector<int> W_1(n);
    maximum_weighted_matching(g, &W_1[0]);
    for(int i=0; i<n; i++) {
        if(W_1[i] > i) {
            W.add(i, W_1[i]);
            fu.Union(i, W_1[i]);
        }
    }

    for(int i=0; i<n; i++) {
        if(!visited[i]) { // not visited cycle
            int prev = -1;
            int v = i;
            pair<int,int> edge_to_transfer = {-1,-1};
            do {
                visited[v] = true;
                if(C[v].first != prev) {
                    prev = v;
                    v = C[v].first;
                } else {
                    prev = v;
                    v = C[v].second;
                }
                if(!W.contains(prev, v) && fu.canUnion(prev, v)) {
                    edge_to_transfer = {prev, v};
                }
            } while(v != i);
            
            C.remove(edge_to_transfer);
            W.add(edge_to_transfer);
            fu.Union(edge_to_transfer.first, edge_to_transfer.second);
        }
    }

    if(C.weight_sum() >= W.weight_sum()) {
        matching = C;
    } else {
        matching = W;
    }

    delete visited;
}