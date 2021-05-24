#include "util.hpp"

struct my_edge {
    int u, v, c;
};

bool by_weight(my_edge a, my_edge b) {
    return a.c>b.c;
}

void finish(const Graph& g, TwoMatching& matching) {
    // initialization
    int n = num_vertices(g);
    my_edge *e = new my_edge[n*(n-1)/2];
    FindUnion fu(n);

    // preparing array with edges sorted by weight
    int counter = 0;
    for(int i=0; i<n; i++) {
        for(int j=i+1; j<n; j++) {
            e[counter++] = {i, j, weight(i,j,g)};
        }
    }
    std::sort(e, e+counter, by_weight);

    // updating FindUnion with edges from matching
    for(int i=0; i<n; i++) {
        if(matching[i].first > i) {
            fu.Union(i, matching[i].first);
        }
        if(matching[i].second > i) {
            fu.Union(i, matching[i].second);
        }
    }

    // greedy selection of remaining edges
    for(int i=0; i<counter; i++) {
        if(!in_matching(e[i].u, e[i].v, matching) && fu.canUnion(e[i].u, e[i].v)) {
                fu.Union(e[i].u, e[i].v);
                matching_add(e[i].u, e[i].v, matching);
        }
    }

    delete e;
}