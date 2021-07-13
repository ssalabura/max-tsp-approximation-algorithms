#include "util.hpp"
#include "maximum_weighted_2_matching.hpp"

void select(const Graph& g, TwoMatching& matching) {
    int n = num_vertices(g);
    maximum_weighted_2_matching(g, matching);

    bool *visited = new bool[n]();

    for(int i=0; i<n; i++) {
        if(!visited[i]) { // not visited cycle
            int prev = -1;
            int v = i;
            pair<int, int> smallest_edge;
            int smallest_weight = INT_MAX;
            do {
                visited[v] = true;
                if(matching[v].first != prev) {
                    if(weight(v, matching[v].first, g) < smallest_weight) {
                        smallest_edge = {v, matching[v].first};
                        smallest_weight = weight(v, matching[v].first, g);
                    }
                    prev = v;
                    v = matching[v].first;
                } else {
                    if(weight(v, matching[v].second, g) < smallest_weight) {
                        smallest_edge = {v, matching[v].second};
                        smallest_weight = weight(v, matching[v].second, g);
                    }
                    prev = v;
                    v = matching[v].second;
                }
            } while(v != i);

            matching_remove(smallest_edge, matching);
        }
    }

    delete visited;
}