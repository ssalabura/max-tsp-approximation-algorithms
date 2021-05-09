#include "util.hpp"

int main() {
    int n;
    cin >> n;
    Graph g(n);
    TwoMatching matching(n);

    int w;
    for(int i=0; i<n; i++) {
        for(int j=i+1; j<n; j++) {
            cin >> w;
            add_edge(i,j,w,g);
        }
        matching[i] = {-1,-1};
    }

    select(g,matching);
    finish(g,matching);
    optimize(g,matching);
    cout << matching_weight(g,matching);
}