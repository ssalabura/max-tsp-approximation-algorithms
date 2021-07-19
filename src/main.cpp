#include "util.hpp"
#include <iostream>
#include <fstream>
#include <dirent.h>
#include <sys/stat.h>
#include <thread>

Graph read_test(char *path) {
    ifstream file;
    file.open(path);
        
    int n;
    file >> n;
    Graph g(n);

    int w;
    for(int i=0; i<n; i++) {
        for(int j=i+1; j<n; j++) {
            file >> w;
            add_edge(i,j,w,g);
        }
    }

    file.close();
    return g;
}

void compute(const Graph& g, int *result) {
    int n = num_vertices(g);
    TwoMatching matching(n);

    select(g, matching);
    finish(g, matching);
    optimize(g, matching);
    *result = matching.weight_sum(g);
}

const bool PARALLEL = true;

int main(int argc, char *argv[]) {
    if(argc != 2) {
        cout << "Usage: [executable] [directory/file path]" << endl;
    }
    struct stat s;
    if(stat(argv[1],&s) == 0) {
        if(s.st_mode & S_IFDIR) { // DIRECTORY
            chdir(argv[1]);
            struct dirent *de;
            struct stat file_stat;

            DIR *dir = opendir(".");
            int count = 0;
            while(de = readdir(dir)) {
                stat(de->d_name, &file_stat);
                if(file_stat.st_mode & S_IFREG) count++;
            }
            closedir(dir);

            int *result = new int[count];
            thread *threads = new thread[count];
            int counter = 0;
            dir = opendir(".");
            while(de = readdir(dir)) {
                stat(de->d_name, &file_stat);
                if(file_stat.st_mode & S_IFREG) {
                    Graph g = read_test(de->d_name);
                    if(PARALLEL) {
                        threads[counter] = thread(compute, g, &result[counter]);
                    } else {
                        compute(g, &result[counter]);
                    }
                    counter++;
                }
            }
            closedir(dir);

            int sum = 0;
            for(int i=0; i<count; i++) {
                if(PARALLEL) {
                    threads[i].join();
                }
                sum += result[i];
            }

            cout.precision(2);
            cout << fixed << (float)sum/count;

            delete result;
            return 0;
        }
        else if(s.st_mode & S_IFREG) { // REGULAR FILE
            Graph g = read_test(argv[1]);
            int result;
            compute(g, &result);
            cout << result;

            return 0;
        }
        else {
            cerr << "error: wrong file mode";
            return 1;
        }
    } else {
        cerr << "error: unable to open file";
        return 1;
    }
}