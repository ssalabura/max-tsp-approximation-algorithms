#include "util.hpp"

const int MAX = 25;

bool inS(int v, int s) {
    return (s & (1<<(v-1))) > 0;
}

int without(int v, int s) {
    return s - (1<<(v-1));
}

int f[MAX][1<<(MAX-1)];

int maxtsp(const Graph& g) {
    // TODO: transform into select function

    int n = num_vertices(g);
    if(n > MAX) return;

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