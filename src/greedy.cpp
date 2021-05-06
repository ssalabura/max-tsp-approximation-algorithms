#include "headers.hpp"

struct my_edge {
    int u, v, c;
};

bool by_weight(my_edge a, my_edge b) {
    return a.c>b.c;
}

int *parent, *my_rank, *d;

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
    d[u]++;
    d[v]++;
}

int maxtsp(const Graph& g) {
    int n = num_vertices(g);

    my_edge *e = new my_edge[n*(n-1)/2];
    parent = new int[n];
    my_rank = new int[n];
    d = new int[n]();

    for(int i=0; i<n; i++) {
        parent[i] = i;
        my_rank[i] = 0;
    }
    int counter = 0;
    for(int i=0; i<n; i++) {
        for(int j=i+1; j<n; j++) {
            e[counter++] = {i,j,weight(i,j,g)};
        }
    }

    std::sort(e, e+counter, by_weight);

    int output = 0, edges = 0;
    for(int i=0; i<counter; i++) {
        if(d[e[i].u] < 2 && d[e[i].v] < 2) {
            if(d[e[i].u] == 1 && d[e[i].v] == 1 && edges < n-1 && Find(e[i].u) == Find(e[i].v)) { // powstanie niechciany cykl
                continue;
            }
            output += e[i].c;
            edges++;
            Union(e[i].u, e[i].v);
        }
    }

    delete e, parent, my_rank, d;
    return output;
}