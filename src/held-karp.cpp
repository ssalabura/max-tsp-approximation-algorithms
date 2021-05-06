#include "headers.hpp"

bool inS(int v, int s) {
    return (s & (1<<(v-1))) > 0;
}

int without(int v, int s) {
    return s - (1<<(v-1));
}

int f[20][1<<19];

int maxtsp(const Graph& g) {
    int n = num_vertices(g);
    if(n > 20) return -1;

    for(int v=1; v<n; v++) {
        f[v][0] = weight(0,v,g);
    }

    int s;
    for(s=1; s < (1<<n-1)-1; s++) {
        for(int v=1; v<n; v++) {
            if(!inS(v,s)) {
                int best = -1;
                for(int i=1; i<n; i++) {
                    if(inS(i,s)) {
                        best = max(best, f[i][without(i,s)] + weight(i,v,g));
                    }
                }
                f[v][s] = best;
            }
        }
    }

    int best = -1;
    for(int i=1; i<n; i++) {
        best = max(best, f[i][without(i,s)] + weight(i,0,g));
    }
    return best;
}