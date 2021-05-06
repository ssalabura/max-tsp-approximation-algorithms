#include "maximum_weighted_2_matching.hpp"

int maxtsp(const Graph& g) {
    vector< pair<int,int> > mate(num_vertices(g));
    return maximum_weighted_2_matching(g, mate);
}