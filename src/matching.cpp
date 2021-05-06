#include "maximum_weighted_2_matching.hpp"

bool *visited;
int smallest_edge;

void dfs(int v, vector< pair<int,int> >& mate, const Graph& g) {
    visited[v] = true;
    if(!visited[mate[v].first]) {
        smallest_edge = min(smallest_edge, weight(v,mate[v].first,g));
        dfs(mate[v].first,mate,g);
    }
    if(!visited[mate[v].second]) {
        smallest_edge = min(smallest_edge, weight(v,mate[v].second,g));
        dfs(mate[v].second,mate,g);
    }
}

int maxtsp(const Graph& g) {
    int n = num_vertices(g);
    vector< pair<int,int> > mate(n);
    int weight_sum = maximum_weighted_2_matching(g, mate);

    visited = new bool[n]();

    for(int i=0; i<n; i++) {
        if(!visited[i] && mate[i].second != -1) {
            smallest_edge = INT_MAX;
            dfs(i,mate,g);
            weight_sum -= smallest_edge;
        }
    }

    delete visited;
    return weight_sum;
}