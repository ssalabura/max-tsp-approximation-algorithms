#include "maximum_weighted_2_matching.hpp"

int maxtsp(const Graph& g) {
    vector< pair<int,int> > mate(num_vertices(g));
    int output = maximum_weighted_2_matching(g, mate);
    for(int i=0; i<num_vertices(g); i++) {
        cout << i << ": " << mate[i].first << ", " << mate[i].second << endl;
    }
    return output;
}