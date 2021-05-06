#include "headers.hpp"

// outer vertices: 2ni   -- 2ni+n-1
// inner vertices: 2ni+n -- 2n(i+1)-1
// core vertices: 2ni+i, 2ni+n+i

int maximum_weighted_2_matching(const Graph &g, vector< pair<int,int> > &matching) {
    int n = num_vertices(g);
    int MAX_WEIGHT = 1001;
    Graph g_prime(2*n*n);
    for(int i=0; i<n; i++) {
        // core vertices
        int core1 = 2*n*i+i;
        int core2 = 2*n*i+n+i;
        // core edges
        for(int inner=2*n*i+n; inner<2*n*(i+1); inner++) {
            if(inner != core2) {
                add_edge(inner,core1,MAX_WEIGHT,g_prime);
                add_edge(inner,core2,MAX_WEIGHT,g_prime);
                add_edge(core1,inner,MAX_WEIGHT,g_prime);
                add_edge(core2,inner,MAX_WEIGHT,g_prime);
            }
        }
        // inner edges
        for(int j=0; j<n; j++) {
            if(j != i) {
                int outer = 2*n*i+j;
                int inner = 2*n*i+n+j;
                add_edge(outer,inner,MAX_WEIGHT,g_prime);
                add_edge(inner,outer,MAX_WEIGHT,g_prime);
            }
        }
        // outer edges
        for(int j=0; j<n; j++) {
            if(j != i) {
                int my_outer = 2*n*i+j;
                int other_outer = 2*n*j+i;
                int w = weight(i,j,g);
                add_edge(my_outer,other_outer,w,g_prime);
                add_edge(other_outer,my_outer,w,g_prime);
            }
        }
    }
    vector<int> mate(2*n*n);
    maximum_weighted_matching(g_prime, &mate[0]);
    return matching_weight_sum(g_prime, &mate[0])-n*(n-1)*MAX_WEIGHT;
}