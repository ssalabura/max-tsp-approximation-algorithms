#include "util.hpp"
#include "maximum_weighted_2_matching.hpp"

void select(const Graph& g, TwoMatching& matching) {
    int n = num_vertices(g);
    maximum_weighted_2_matching(g, matching);

    bool *visited = new bool[n]();

    for(int i=0; i<n; i++) {
        if(!visited[i]) {
            int prev = -1;
            int v = i;
            pair<int, int> smallest_edge;
            int smallest_weight = INT_MAX;
            do {
                visited[v] = true;
                if(matching[v].first != prev) {
                    prev = v;
                    v = matching[v].first;
                } else {
                    prev = v;
                    v = matching[v].second;
                }
                if(weight(prev, v, g) < smallest_weight) {
                    smallest_edge = {prev, v};
                    smallest_weight = weight(prev, v, g);
                }
            } while(v != i);

            matching.remove(smallest_edge);
        }
    }

    delete visited;
}