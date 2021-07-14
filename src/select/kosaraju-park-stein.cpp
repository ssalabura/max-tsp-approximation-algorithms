#include "util.hpp"
#include "maximum_weighted_2_matching.hpp"
#include <boost/graph/maximum_weighted_matching.hpp>
#include <iostream>

void select(const Graph& g, TwoMatching& matching) {
    int n = num_vertices(g);
    TwoMatching C(n);
    maximum_weighted_2_matching(g, C);

    bool *visited = new bool[n]();
    int *rep_id = new int[n]; // if x is representative then rep_id[x] is its new vertex id, else rep_id[x]=x
    int *f = new int[n]; // edge of a cycle whose head is incident to x (edge is f[x] -> x)
    int *w = new int[n+n/3]; // w[x] - weight of a cycle where x=rep_id (bigger than needed for readability)

    int rep_id_counter = n;
    for(int i=0; i<n; i++) {
        if(!visited[i]) {
            int prev = -1;
            int v = i;
            int rep_count = 0;
            int cycle_weight = 0;
            do {
                visited[v] = true;
                if(rep_count < 3) {
                    rep_id[v] = rep_id_counter;
                    rep_count++;
                } else {
                    rep_id[v] = v;
                }

                if(C[v].first != prev) {
                    prev = v;
                    v = C[v].first;
                } else {
                    prev = v;
                    v = C[v].second;
                }
                f[v] = prev;
                cycle_weight += weight(prev, v, g);
            } while(v != i);
            w[rep_id_counter] = cycle_weight;
            rep_id_counter++;
        }
    }

    Graph g_prime(rep_id_counter);
    int *in_rep = new int[rep_id_counter*rep_id_counter]; // in_rep[x*rep_id_counter+y] - internal vertex of a representative x in edge x<->y (bigger than needed for readability)

    for(int i=0; i<n; i++) {
        for(int j=i+1; j<n; j++) {
            if(rep_id[i] != rep_id[j]) {
                int edge_weight = weight(i,j,g) - weight(f[i],i,g) - weight(f[j],j,g);
                if(rep_id[i] != i) edge_weight += w[rep_id[i]];
                if(rep_id[j] != j) edge_weight += w[rep_id[j]];
                if(edge_weight > weight(rep_id[i], rep_id[j], g_prime)) {
                    remove_edge(rep_id[i], rep_id[j], g_prime);
                    add_edge(rep_id[i], rep_id[j], edge_weight, g_prime);
                    if(rep_id[i] != i) {
                        in_rep[rep_id[i]*rep_id_counter+rep_id[j]] = i;
                    }
                    if(rep_id[j] != j) {
                        in_rep[rep_id[j]*rep_id_counter+rep_id[i]] = j;
                    }
                }
                // cout << "add_edge " << rep_id[i] << " " << rep_id[j] << " " << edge_weight << endl;
            }
        }
    }
    vector<int> M(rep_id_counter);
    maximum_weighted_matching(g_prime, &M[0]);

    int *V = new int[n*n](); // (almost) as in paper, edge x<->y is included max{V[x*n+y],0}/2 times (so either 1 or 0)
    for(int i=0; i<rep_id_counter; i++) {
        if(M[i] != -1) {
            int x = (i >= n ? in_rep[i*rep_id_counter+M[i]] : i);
            int y = (M[i] >= n ? in_rep[M[i]*rep_id_counter+i] : M[i]);
            // cout << i << " <--> " << M[i] << ", (" << x << " <--> " << y << ")" << endl;
            V[x*n+y]++; V[y*n+x]++; // adding e
            V[f[x]*n+x]--; V[x*n+f[x]]--; // removing f_x
            V[f[y]*n+y]--; V[y*n+f[y]]--; // removing f_y
            // if x is representative, adding C_x
            if(i >= n) {
                int v = x, prev = -1;
                do {
                    if(C[v].first != prev) {
                        prev = v;
                        v = C[v].first;
                    } else {
                        prev = v;
                        v = C[v].second;
                    }
                    V[prev*n+v]++; V[v*n+prev]++;
                } while(v != x);
            }
            // if y is representative, adding C_y
            if(M[i] >= n) {
                int v = y, prev = -1;
                do {
                    if(C[v].first != prev) {
                        prev = v;
                        v = C[v].first;
                    } else {
                        prev = v;
                        v = C[v].second;
                    }
                    V[prev*n+v]++; V[v*n+prev]++;
                } while(v != y);
            }
        }
    }
    for(int i=0; i<n; i++) {
        for(int j=i+1; j<n; j++) {
            if(V[i*n+j] != 0 && V[i*n+j] != 2) cerr << "error (?): V[" << i << "," << j << "] = " << V[i*n+j] << endl;
            else if(V[i*n+j] == 2) {
                matching_add(i,j,matching);
            }
        }
    }

    // TODO: add "almost cycle" to output
    for(int i=n; i<rep_id_counter; i++) {
        if(M[i] == -1) cout << i << " not matched!" << endl;
    }

    delete visited, rep_id, f, w, in_rep;
}