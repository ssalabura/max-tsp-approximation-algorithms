#include "util.hpp"
#include <iostream>

int weight(int u, int v, const Graph& g) {
    return get(edge_weight, g, edge(u,v,g).first);
}

TwoMatching::TwoMatching(int n) : n(n) { 
    mate = new pair<int, int>[n];
    clear();
}

TwoMatching::~TwoMatching() { 
    delete mate;
}

void TwoMatching::clear() {
    for(int i=0; i<n; i++) {
        mate[i] = {-1,-1};
    }
}

void TwoMatching::add(int u, int v) {
    if(mate[u].first == -1) {
        mate[u].first = v;
    } else if(mate[u].second == -1 && mate[u].first != v) {
        mate[u].second = v;
    } else if(mate[u].first != v && mate[u].second != v) {
        cerr << "Unable to add (" << u << "," << v << ") to matching." << endl;
    }

    if(mate[v].first == -1) {
        mate[v].first = u;
    } else if(mate[v].second == -1 && mate[v].first != u) {
        mate[v].second = u;
    } else if(mate[v].first != u && mate[v].second != u){
        cerr << "Unable to add (" << v << "," << u << ") to matching." << endl;
    }
}

void TwoMatching::add(pair<int,int> edge) {
    add(edge.first, edge.second);
}

void TwoMatching::remove(int u, int v) {
    if(mate[u].first == v) {
        mate[u].first = mate[u].second;
        mate[u].second = -1;
    } else if(mate[u].second == v) {
        mate[u].second = -1;
    } else {
        cerr << "Unable to remove (" << u << "," << v << ") from matching." << endl;
    }

    if(mate[v].first == u) {
        mate[v].first = mate[v].second;
        mate[v].second = -1;
    } else if(mate[v].second == u) {
        mate[v].second = -1;
    } else {
        cerr << "Unable to remove (" << v << "," << u << ") from matching." << endl;
    }
}

void TwoMatching::remove(pair<int,int> edge) {
    remove(edge.first, edge.second);
}

bool TwoMatching::contains(int u, int v) {
    return mate[u].first == v || mate[u].second == v;
}

int TwoMatching::weight_sum(const Graph& g) {
    int sum = 0;
    for(int i=0; i<n; i++) {
        if(mate[i].first != -1) {
            sum += weight(i, mate[i].first, g);
        }
        if(mate[i].second != -1) {
            sum += weight(i, mate[i].second, g);
        }
    }
    return sum/2;
}

pair<int,int> TwoMatching::operator[](int i) {
    return mate[i];
}

TwoMatching& TwoMatching::operator=(const TwoMatching& other) {
    for(int i=0; i<n; i++) {
        mate[i] = other.mate[i];
    }
}

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