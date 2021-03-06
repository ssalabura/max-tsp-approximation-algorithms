#include "util.hpp"
#include "maximum_weighted_2_matching.hpp"
#include <boost/graph/maximum_weighted_matching.hpp>
#include <iostream>

// outer vertices: 2ni   -- 2ni+n-1
// inner vertices: 2ni+n -- 2n(i+1)-1
// core vertices: 2ni+i, 2ni+n+i

void maximum_weighted_2_matching(const Graph& g, TwoMatching& matching) {
    int n = num_vertices(g);
    int MAX_WEIGHT = 1500;
    SparseGraph g_prime(2*n*n);

    for(int i=0; i<n; i++) {
        // core vertices
        int core1 = 2*n*i+i;
        int core2 = 2*n*i+n+i;
        // core edges
        for(int inner=2*n*i+n; inner<2*n*(i+1); inner++) {
            if(inner != core2) {
                add_edge(inner,core1,3*MAX_WEIGHT,g_prime);
                add_edge(inner,core2,3*MAX_WEIGHT,g_prime);
            }
        }
        // inner edges
        for(int j=0; j<n; j++) {
            if(j != i) {
                int outer = 2*n*i+j;
                int inner = 2*n*i+n+j;
                add_edge(outer,inner,2*MAX_WEIGHT,g_prime);
            }
        }
        // outer edges
        for(int j=0; j<n; j++) {
            if(j != i) {
                int my_outer = 2*n*i+j;
                int other_outer = 2*n*j+i;
                int w = weight(i,j,g);
                add_edge(my_outer,other_outer,w+MAX_WEIGHT,g_prime);
            }
        }
    }
    vector<int> mate(2*n*n);
    maximum_weighted_matching(g_prime, &mate[0]);
    for(int i=0; i<n; i++) {
        int core1 = 2*n*i+i;
        for(int outer=2*n*i; outer<2*n*i+n; outer++) {
            if(outer != core1 && mate[outer] != outer+n && mate[outer] != -1) {
                // cout << "adding " << i << ", " << mate[outer]/(2*n) << endl;
                matching.add(i, mate[outer]/(2*n));
            }
        }
    }
}