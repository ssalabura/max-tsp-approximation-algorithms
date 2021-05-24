#include "util.hpp"
#include <iostream>

FindUnion::FindUnion(int n) : n(n) {
    parent = new int[n];
    rank = new int[n]();
    d = new int[n]();
    for(int i=0; i<n; i++) {
        parent[i] = i;
    }
    edges_count = 0;
}

FindUnion::~FindUnion() {
    delete parent, rank, d;
}

int FindUnion::Find(int v) {
    if(parent[v] == v) {
        return v;
    }
    parent[v] = Find(parent[v]);
    return parent[v];
}

void FindUnion::Union(int u, int v) {
    int x = Find(u);
    int y = Find(v);
    if(rank[x] > rank[y]) {
        parent[y] = x;
    } else if(rank[x] < rank[y]) {
        parent[x] = y;
    } else {
        parent[y] = x;
        rank[x]++;
    }
    edges_count++;
    d[u]++;
    d[v]++;
}

bool FindUnion::canUnion(int u, int v) {
    return (d[u] < 2 && d[v] < 2 && !(Find(u) == Find(v) && edges_count < n-1));
}

int weight(int u, int v, const Graph& g) {
    return get(edge_weight, g, edge(u,v,g).first);
}

void matching_empty(int n, TwoMatching& matching) {
    for(int i=0; i<n; i++) {
        matching[i] = {-1,-1};
    }
}

void matching_add(int u, int v, TwoMatching& matching) {
    if(matching[u].first == -1) {
        matching[u].first = v;
    } else if(matching[u].second == -1) {
        matching[u].second = v;
    } else {
        cerr << "Unable to add (" << u << "," << v << ") to matching." << endl;
    }

    if(matching[v].first == -1) {
        matching[v].first = u;
    } else if(matching[v].second == -1) {
        matching[v].second = u;
    } else {
        cerr << "Unable to add (" << v << "," << u << ") to matching." << endl;
    }
}

void matching_remove(int u, int v, TwoMatching& matching) {
    if(matching[u].first == v) {
        matching[u].first = matching[u].second;
        matching[u].second = -1;
    } else if(matching[u].second == v) {
        matching[u].second = -1;
    } else {
        cerr << "Unable to remove (" << u << "," << v << ") from matching." << endl;
    }

    if(matching[v].first == u) {
        matching[v].first = matching[v].second;
        matching[v].second = -1;
    } else if(matching[v].second == u) {
        matching[v].second = -1;
    } else {
        cerr << "Unable to remove (" << v << "," << u << ") from matching." << endl;
    }
}

bool in_matching(int u, int v, TwoMatching& matching) {
    return matching[u].first == v || matching[u].second == v;
}

int matching_weight(const Graph& g, TwoMatching& matching) {
    int n = num_vertices(g);
    int sum = 0;
    for(int i=0; i<n; i++) {
        if(matching[i].first != -1) {
            sum += weight(i,matching[i].first,g);
        }
        if(matching[i].second != -1) {
            sum += weight(i,matching[i].second,g);
        }
    }
    return sum/2;
}