#include "headers.hpp"

int *tour;

int maxtsp(const Graph& g) {
    int n = num_vertices(g);
    tour = new int[n+1];
    for(int i=0; i<n; i++) {
        tour[i] = i;
    }
    tour[n] = 0;

    while(true) {
        bool flag = false;
        for(int i=1; i<n; i++) {
            for(int j=i+1; j<n; j++) {
                if(weight(tour[i-1],tour[j],g) + weight(tour[i],tour[j+1],g) > weight(tour[i-1],tour[i],g) + weight(tour[j],tour[j+1],g)) {
                    std::reverse(tour+i, tour+j+1);
                    flag = true;
                }
            }
        }
        if(!flag) break;
    }

    int output = 0;
    for(int i=0; i<n; i++) {
        output += weight(tour[i],tour[i+1],g);
    }
    delete tour;
    return output;
}