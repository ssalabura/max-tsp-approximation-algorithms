#include "util.hpp"

void finish(const Graph& g, TwoMatching& matching) {
    int n = num_vertices(g);
    bool *visited = new bool[n]();

    // start from a vertex that is not in the middle of some path
    int start = 0;
    while(matching[start].second != -1) {
        start++;
        if(start == n) {
            delete[] visited;
            return;
        }
    }

    // main loop
    int v = start;
    while(true) {
        visited[v] = true;
        if(matching[v].first != -1 && !visited[matching[v].first]) {
            v = matching[v].first;
        } else if(matching[v].second != -1 && !visited[matching[v].second]) {
            v = matching[v].second;
        } else {
            int best_weight = -1, next_v = -1;
            for(int i=0; i<n; i++) {
                if(!visited[i] && matching[i].second == -1 && weight(v,i,g) > best_weight) {
                    best_weight = weight(v,i,g);
                    next_v = i;
                }
            }
            if(next_v == -1) break;
            matching.add(v, next_v);
            v = next_v;
        }
    }
    matching.add(v, start);
    
    delete[] visited;
}