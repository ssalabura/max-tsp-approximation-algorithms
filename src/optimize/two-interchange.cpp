#include "util.hpp"

int *tour;

void optimize(const Graph& g, TwoMatching& matching) {
    int n = num_vertices(g);

    // translate matching to tour
    tour = new int[n+1];
    tour[0] = 0;
    tour[1] = matching[0].first;
    int pprev = 0, prev = tour[1];
    for(int i=2; i<n; i++) {
        if(matching[prev].first != pprev) {
            tour[i] = matching[prev].first;
        } else {
            tour[i] = matching[prev].second;
        }
        pprev = prev;
        prev = tour[i];
    }
    tour[n] = 0;

    // main loop
    while(true) {
        bool flag = false;
        for(int i=1; i<n; i++) {
            for(int j=i+1; j<n; j++) {
                if(weight(tour[i-1],tour[j],g) + weight(tour[i],tour[j+1],g) > weight(tour[i-1],tour[i],g) + weight(tour[j],tour[j+1],g)) {
                    std::reverse(tour+i, tour+j+1);
                    flag = true;
                }
            }
        }
        if(!flag) break;
    }

    // translate back to matching
    matching[0] = {tour[1], tour[n-1]};
    for(int i=1; i<n; i++) {
        int current = tour[i];
        matching[current] = {tour[i-1], tour[i+1]};
    }

    delete tour;
    return;
}