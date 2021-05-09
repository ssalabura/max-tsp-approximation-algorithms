#include "util.hpp"

int maxtsp(const Graph& g) {
    // TODO: transform into finish function
    int n = num_vertices(g);
    bool *visited = new bool[n]();
    int output = 0;

    int v = 0;
    while(true) {
        visited[v] = true;
        int best = -1, next = -1;
        for(int i=0; i<n; i++) {
            if(!visited[i] && weight(v,i,g) > best) {
                best = weight(v,i,g);
                next = i;
            }
        }
        if(next == -1) break;
        output += best;
        v = next;
    }
    output += weight(v,0,g);
    
    delete visited;
    return output;
}