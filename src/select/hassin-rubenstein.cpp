#include "util.hpp"
#include "maximum_weighted_2_matching.hpp"
#include "max_tsp_exact.hpp"
#include <iostream>

int epsilon = 0; // A1 works exactly like matching heuristic

void A1(const Graph& g, TwoMatching& C, TwoMatching& matching) {
    int n = num_vertices(g);
    bool *visited = new bool[n]();

    matching = C;

    for(int i=0; i<n; i++) {
        if(!visited[i]) { // not visited cycle
            int prev = -1;
            int v = i;
            vector<int> cycle;
            pair<int, int> smallest_edge;
            int smallest_weight = INT_MAX;
            do {
                visited[v] = true;
                cycle.push_back(v);
                if(C[v].first != prev) {
                    prev = v;
                    v = C[v].first;
                } else {
                    prev = v;
                    v = C[v].second;
                }
                if(weight(prev, v, g) < smallest_weight) {
                    smallest_edge = {prev, v};
                    smallest_weight = weight(prev, v, g);
                }
            } while(v != i);

            if(cycle.size() > epsilon) {
                matching.remove(smallest_edge);
            } else {
                for(int j=0; j<cycle.size()-1; j++) {
                    matching.remove(cycle[j], cycle[j+1]);
                }
                matching.remove(cycle[cycle.size()-1], cycle[0]);
                Graph c(cycle.size()+1);
                TwoMatching c_matching(cycle.size()+1);
                for(int j=0; j<cycle.size(); j++) {
                    for(int k=0; k<cycle.size(); k++) {
                        add_edge(j, k, weight(cycle[j], cycle[k], g), c);
                    }
                    add_edge(j, cycle.size(), 0, c);
                }
                max_tsp_exact(c, c_matching);
                for(int j=0; j<cycle.size(); j++) {
                    if(c_matching[j].first != -1 && c_matching[j].first != cycle.size()) {
                        matching.add(cycle[j], cycle[c_matching[j].first]);
                    }
                    if(c_matching[j].second != -1 && c_matching[j].second != cycle.size()) {
                        matching.add(cycle[j], cycle[c_matching[j].second]);
                    }
                }
            }
        }
    }

    delete visited;
}

void A2(const Graph& g, TwoMatching& C, TwoMatching& matching1, TwoMatching& matching2) {
    
}

void select(const Graph& g, TwoMatching& matching) {
    int n = num_vertices(g);
    TwoMatching C(n);
    maximum_weighted_2_matching(g, C);
    TwoMatching T1(n), T2(n), T3(n);
    A1(g, C, T1);
    A2(g, C, T2, T3);
    int w1 = T1.weight_sum(g);
    int w2 = T2.weight_sum(g);
    int w3 = T3.weight_sum(g);
    if(w1 > w2 && w1 > w3) {
        matching = T1;
    } else if(w2 > w1 && w2 > w3) {
        matching = T2;
    } else {
        matching = T3;
    }
}