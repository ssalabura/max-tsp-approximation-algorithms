#include "util.hpp"
#include "maximum_weighted_2_matching.hpp"
#include "max_tsp_exact.hpp"
#include <boost/graph/maximum_weighted_matching.hpp>
#include <random>
#include <sys/time.h>
#include <iostream>

int epsilon = 0; // A1 works exactly like matching heuristic

void A1(const Graph& g, TwoMatching& C, TwoMatching& matching) {
    int n = num_vertices(g);
    bool *visited = new bool[n]();

    matching = C;

    for(int i=0; i<n; i++) {
        if(!visited[i]) {
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
                // removing original cycle
                for(int j=0; j<cycle.size()-1; j++) {
                    matching.remove(cycle[j], cycle[j+1]);
                }
                matching.remove(cycle[cycle.size()-1], cycle[0]);
                // creating subgraph with vertices only from this cycle (plus additional one for reduction to max-TSP)
                Graph c(cycle.size()+1);
                TwoMatching c_matching(cycle.size()+1);
                for(int j=0; j<cycle.size(); j++) {
                    for(int k=0; k<cycle.size(); k++) {
                        add_edge(j, k, weight(cycle[j], cycle[k], g), c);
                    }
                    add_edge(j, cycle.size(), 0, c);
                }
                max_tsp_exact(c, c_matching);
                // adding hamiltonian path to our matching
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

    delete[] visited;
}

void A2(const Graph& g, TwoMatching& C, TwoMatching& matching1, TwoMatching& matching2) {
    int n = num_vertices(g);
    // random engine based on time
    struct timeval time_now{};
    gettimeofday(&time_now, nullptr);
    auto engine = default_random_engine();
    
    // creating FindUnion to find edges connecting vertices from different cycles
    FindUnion C_fu(n);
    for(int i=0; i<n; i++) {
        if(C[i].first > i) {
            C_fu.Union(i, C[i].first);
        }
        if(C[i].second > i) {
            C_fu.Union(i, C[i].second);
        }
    }

    // creating M' and W
    Graph g_prime(n);
    for(int i=0; i<n; i++) {
        for(int j=i+1; j<n; j++) {
            if(C_fu.Find(i) != C_fu.Find(j)) {
                add_edge(i, j, weight(i,j,g), g_prime);
            }
        }
    }
    vector<int> M_prime(n), W1(n);
    maximum_weighted_matching(g_prime, &M_prime[0]);
    maximum_weighted_matching(g, &W1[0]);
    
    TwoMatching W(g), P(g);
    P = C;
    FindUnion W_fu(n);
    for(int i=0; i<n; i++) {
        if(W1[i] > i) {
            W.add(i, W1[i]);
            W_fu.Union(i, W1[i]);
        }
    }

    // for every cycle: constructing matchings M1 and M2 and randomly trasferring them to W
    bool *visited = new bool[n]();
    auto rand_bool = bind(uniform_int_distribution<>(0,1), engine);
    for(int i=0; i<n; i++) {
        if(!visited[i]) {
            int prev = -1;
            int v = i;
            vector<int> M1(n), M2(n);
            FindUnion M1_W(n), M2_W(n);
            M1_W = W_fu; M2_W = W_fu;
            bool f = false;
            int v2 = -1, v3 = -1;
            do {
                visited[v] = true;
                if(C[v].first != prev) {
                    prev = v;
                    v = C[v].first;
                } else {
                    prev = v;
                    v = C[v].second;
                }

                if(v2 == -1) {
                    v2 = v;
                } else if(v3 == -1) {
                    v3 = v;
                }
                if(!f) {
                    if(M1_W.Find(prev) != M1_W.Find(v)) {
                        M1[prev] = v;
                        M1[v] = prev;
                        M1_W.Union(prev, v);
                        f = true;
                    }
                } else {
                    if(M2_W.Find(prev) != M2_W.Find(v)) {
                        M2[prev] = v;
                        M2[v] = prev;
                        M2_W.Union(prev, v);
                        f = false;
                    }
                }
            } while(v != i);

            if(M1[v2] == v && M1[v] == prev) { // conflict 1 - e1 and ek is in M1
                M1[v2] = -1; // unmatch e1 in M1
                if(M2[v2] == -1){ // if e2 was skipped then add e1 to M2
                    M2[v] = v2;
                    M2[v2] = v;
                }
            }
            if(M1[v] == -1 && M2[v] == -1) { // conflict 2 - e1 and ek is skipped, add e1 to M2
                M2[v] = v2;
                M2[v2] = v;
            }

            if(rand_bool()) {
                for(int j=0; j<n; j++) {
                    if(M1[j] > j) {
                        W.add(j, M1[j]);
                        W_fu.Union(j, M1[j]);
                        P.remove(j, M1[j]);
                    }
                }
            } else {
                for(int j=0; j<n; j++) {
                    if(M2[j] > j) {
                        W.add(j, M2[j]);
                        W_fu.Union(j, M2[j]);
                        P.remove(j, M2[j]);
                    }
                }
            }
        }
    }
    matching1 = W;

    // changing M' to M as it's no longer needed
    for(int i=0; i<n; i++) {
        if(M_prime[i] != -1) {
            if(P[i].second == -1 && P[M_prime[i]].second == -1) {
                P.add(i, M_prime[i]);
            } else if(!P.contains(i, M_prime[i])) {
                M_prime[M_prime[i]] = -1;
                M_prime[i] = -1;
            }
        } 
    }

    // for every cycle: removing random edge from M
    for(int i=0; i<n; i++) {
        visited[i] = false;
    }
    for(int i=0; i<n; i++) {
        if(!visited[i]) {
            int prev = -1;
            int v = i;
            vector< pair<int,int> > edges_from_M;
            bool f = false;
            do {
                visited[v] = true;
                if(P[v].first != prev) {
                    prev = v;
                    v = P[v].first;
                } else if(P[v].second != -1) {
                    prev = v;
                    v = P[v].second;
                } else { // not a cycle
                    f = true;
                    break;
                }
                if(M_prime[prev] == v) {
                    edges_from_M.push_back({prev, v});
                }
            } while(v != i);
            if(!f) {
                auto rand = bind(uniform_int_distribution<>(0,edges_from_M.size()-1), engine);
                pair<int,int> to_remove = edges_from_M[rand()];
                P.remove(to_remove);
            }
        }
    }
    matching2 = P;

    delete[] visited;
}

void select(const Graph& g, TwoMatching& C, TwoMatching& matching) {
    TwoMatching T1(g), T2(g), T3(g);
    A1(g, C, T1);
    A2(g, C, T2, T3);
    int w1 = T1.weight_sum();
    int w2 = T2.weight_sum();
    int w3 = T3.weight_sum();
    // cout << w1 << ", " << w2 << ", " << w3 << endl;
    if(w1 > w2 && w1 > w3) {
        matching = T1;
    } else if(w2 > w1 && w2 > w3) {
        matching = T2;
    } else {
        matching = T3;
    }
}