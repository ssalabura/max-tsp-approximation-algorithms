#include "maximum_weighted_2_matching.hpp"

int maxtsp(const Graph& g) {
    vector< int > mate(num_vertices(g));
    maximum_weighted_matching(g, &mate[0]);
    return matching_weight_sum(g, &mate[0]);
    // vector< pair<int,int> > mate(num_vertices(g));
    // return maximum_weighted_2_matching(g, mate);
    // cout << mate[0].first << ", " << mate[0].second << endl;
    // cout << mate[1].first << ", " << mate[1].second << endl;
    // cout << mate[2].first << ", " << mate[2].second << endl;
    // cout << mate[3].first << ", " << mate[3].second << endl;
    // cout << mate[4].first << ", " << mate[4].second << endl;
}