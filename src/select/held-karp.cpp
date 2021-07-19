#include "util.hpp"
#include "max_tsp_exact.hpp"

void select(const Graph& g, TwoMatching& matching) {
    max_tsp_exact(g, matching);
}