#include "../maximum_weighted_2_matching.hpp"

bool *visited;
pair<int, int> smallest_edge;
int smallest_weight;

void dfs(int v, TwoMatching& matching, const Graph& g) {
    visited[v] = true;
    if(!visited[matching[v].first]) {
        if(weight(v, matching[v].first, g) < smallest_weight) {
            smallest_edge = {v, matching[v].first};
            smallest_weight = weight(v, matching[v].first, g);
        }
        dfs(matching[v].first,matching,g);
    }
    if(!visited[matching[v].second]) {
        if(weight(v, matching[v].second, g) < smallest_weight) {
            smallest_edge = {v, matching[v].second};
            smallest_weight = weight(v, matching[v].second, g);
        }
        dfs(matching[v].second,matching,g);
    }
}

void select(const Graph& g, TwoMatching& matching) {
    int n = num_vertices(g);
    int weight_sum = maximum_weighted_2_matching(g, matching);

    visited = new bool[n]();

    for(int i=0; i<n; i++) {
        if(!visited[i] && matching[i].second != -1) {
            smallest_weight = INT_MAX;
            dfs(i,matching,g);
            matching_remove(smallest_edge.first, smallest_edge.second, matching);
        }
    }

    delete visited;
}