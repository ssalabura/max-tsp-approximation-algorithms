#include "../util.hpp"

struct my_edge {
    int u, v, c;
};

bool by_weight(my_edge a, my_edge b) {
    return a.c>b.c;
}

int *parent, *my_rank, *d;
int edges_count;

int Find(int v) {
    if(parent[v] == v) {
        return v;
    }
    parent[v] = Find(parent[v]);
    return parent[v];
}

void Union(int u, int v) {
    int x = Find(u);
    int y = Find(v);
    if(my_rank[x] > my_rank[y]) {
        parent[y] = x;
    } else if(my_rank[x] < my_rank[y]) {
        parent[x] = y;
    } else {
        parent[y] = x;
        my_rank[x]++;
    }
    edges_count++;
    d[u]++;
    d[v]++;
}

void finish(const Graph& g, TwoMatching& matching) {
    // initialization
    int n = num_vertices(g);
    my_edge *e = new my_edge[n*(n-1)/2];
    parent = new int[n];
    my_rank = new int[n];
    d = new int[n]();
    for(int i=0; i<n; i++) {
        parent[i] = i;
        my_rank[i] = 0;
    }

    // preparing array with edges sorted by weight
    int counter = 0;
    for(int i=0; i<n; i++) {
        for(int j=i+1; j<n; j++) {
            e[counter++] = {i, j, weight(i,j,g)};
        }
    }
    std::sort(e, e+counter, by_weight);

    edges_count = 0;

    // selecting edges from matching
    for(int i=0; i<n; i++) {
        if(matching[i].first > i) {
            Union(i, matching[i].first);
        }
        if(matching[i].second > i) {
            Union(i, matching[i].second);
        }
    }

    // greedy selection of remaining edges
    for(int i=0; i<counter; i++) {
        if(!in_matching(e[i].u, e[i].v, matching) &&
            d[e[i].u] < 2 && d[e[i].v] < 2 && 
            !(Find(e[i].u) == Find(e[i].v) && edges_count < n-1)) {
                Union(e[i].u, e[i].v);
                matching_add(e[i].u, e[i].v, matching);
        }
    }

    delete e, parent, my_rank, d;
}