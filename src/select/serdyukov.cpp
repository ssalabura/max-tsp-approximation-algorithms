#include "util.hpp"
#include "maximum_weighted_2_matching.hpp"
#include <boost/graph/maximum_weighted_matching.hpp>

void select(const Graph& g, TwoMatching& matching) {
    int n = num_vertices(g);
    bool *visited = new bool[n]();
    FindUnion fu(n);
    TwoMatching C(n), W(n);
    matching_empty(n, C);
    matching_empty(n, W);

    maximum_weighted_2_matching(g, C);
    vector<int> W_1(n);
    maximum_weighted_matching(g, &W_1[0]);
    for(int i=0; i<n; i++) {
        if(W_1[i] > i) {
            matching_add(i, W_1[i], W);
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
                    if(!in_matching(v, C[v].first, W) && fu.canUnion(v, C[v].first)) {
                        edge_to_transfer = {v, C[v].first};
                    }
                    prev = v;
                    v = C[v].first;
                } else {
                    if(!in_matching(v, C[v].second, W) && fu.canUnion(v, C[v].second)) {
                        edge_to_transfer = {v, C[v].second};
                    }
                    prev = v;
                    v = C[v].second;
                }
            } while(v != i);
            
            
            matching_remove(edge_to_transfer, C);
            matching_add(edge_to_transfer, W);
            fu.Union(edge_to_transfer.first, edge_to_transfer.second);
        }
    }

    if(matching_weight(g,C) >= matching_weight(g,W)) {
        for(int i=0; i<n; i++) {
            matching[i] = C[i];
        }
    } else {
        for(int i=0; i<n; i++) {
            matching[i] = W[i];
        }
    }

    delete visited;
}