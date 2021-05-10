#include "../util.hpp"

const int MAX = 20;

bool inS(int v, int s) {
    return (s & (1<<(v-1))) > 0;
}

int without(int v, int s) {
    return s - (1<<(v-1));
}

int f[MAX][1<<(MAX-1)];
int last[MAX][1<<(MAX-1)];

void select(const Graph& g, TwoMatching& matching) {
    int n = num_vertices(g);
    if(n > MAX) return;

    for(int v=1; v<n; v++) {
        f[v][0] = weight(0,v,g);
        last[v][0] = 0;
    }

    int s;
    for(s=1; s < (1<<n-1)-1; s++) {
        for(int v=1; v<n; v++) {
            if(!inS(v,s)) {
                int best = -1, best_last = -1;
                for(int i=1; i<n; i++) {
                    if(inS(i,s)) {
                        int c = f[i][without(i,s)] + weight(i,v,g);
                        if(c > best) {
                            best = c;
                            best_last = i;
                        }
                    }
                }
                f[v][s] = best;
                last[v][s] = best_last;
            }
        }
    }

    int best = -1, best_last = -1;
    for(int i=1; i<n; i++) {
        int c = f[i][without(i,s)] + weight(i,0,g);
        if(c > best) {
            best = c;
            best_last = i;
        }
    }
    
    int prev = 0;
    while(s != 0) {
        matching_add(prev, best_last, matching);
        s = without(best_last,s);
        prev = best_last;
        best_last = last[best_last][s];
    }
    matching_add(prev, best_last, matching);
}