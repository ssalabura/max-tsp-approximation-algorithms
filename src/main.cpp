#include "util.hpp"
#include "maximum_weighted_2_matching.hpp"
#include <iostream>
#include <fstream>
#include <dirent.h>
#include <sys/stat.h>
#include <thread>

const int MAX_FILES = 1024;
const int MAX_NAME_LENGTH = 256;

void compute(char *path, int *result) {
    ifstream g_file;

    // reading graph
    g_file.open(path);
    if (!g_file.good()) {
        cerr << "error: unable to open file " << path << endl;
        *result = -1;
        return;
    }
        
    int n;
    g_file >> n;
    Graph g(n);

    int w;
    for(int i=0; i<n; i++) {
        for(int j=i+1; j<n; j++) {
            g_file >> w;
            add_edge(i,j,w,g);
        }
    }

    g_file.close();

    //reading 2-matching
    fstream m_file;
    TwoMatching C(g);
    strcat(path, ".2mat");
    m_file.open(path);
    if (!m_file.good()) {
        ofstream new_m_file;
        new_m_file.open(path);
        maximum_weighted_2_matching(g, C);
        for(int i=0; i<n; i++) {
            new_m_file << C[i].first << " " << C[i].second << endl;
        }
        new_m_file.close();
    } else {
        int a,b;
        for(int i=0; i<n; i++) {
            m_file >> a >> b;
            C.add(i,a);
            C.add(i,b);
        }
    }
    m_file.close();

    TwoMatching matching(g);
    select(g, C, matching);
    finish(g, matching);
    optimize(g, matching);
    *result = matching.weight_sum();
}

const bool PARALLEL = true;

int main(int argc, char *argv[]) {
    if(argc != 2) {
        cout << "Usage: [executable] [directory/file path]" << endl;
        return 1;
    }
    struct stat s;
    if(stat(argv[1],&s) == 0) {
        if(s.st_mode & S_IFDIR) { // DIRECTORY
            if(chdir(argv[1]) == -1) return 1;
            struct dirent *de;
            struct stat file_stat;

            int *result = new int[MAX_FILES];
            char **filenames = new char*[MAX_FILES];
            thread *threads;
            if(PARALLEL) {
                threads = new thread[MAX_FILES];
            }
            int counter = 0;
            DIR *dir = opendir(".");
            while(de = readdir(dir)) {
                stat(de->d_name, &file_stat);
                int len = strlen(de->d_name);
                if((file_stat.st_mode & S_IFREG) && strstr(de->d_name, ".2mat") == NULL) {
                    filenames[counter] = new char[MAX_NAME_LENGTH];
                    strcpy(filenames[counter], de->d_name);
                    if(PARALLEL) {
                        threads[counter] = thread(compute, filenames[counter], &result[counter]);
                    } else {
                        compute(filenames[counter], &result[counter]);
                    }
                    counter++;
                }
            }
            closedir(dir);

            int sum = 0;
            for(int i=0; i<counter; i++) {
                if(PARALLEL) {
                    threads[i].join();
                }
                sum += result[i];
            }

            cout.precision(2);
            cout << fixed << (float)sum/counter;

            delete[] result;
            for(int i=0; i<counter; i++) delete[] filenames[i];
            delete[] filenames;
            if(PARALLEL) {
                delete[] threads;
            }
            return 0;
        }
        else if(s.st_mode & S_IFREG) { // REGULAR FILE
            int result;
            compute(argv[1], &result);
            cout << result;
            return 0;
        }
        else {
            cerr << "error: wrong file mode in " << argv[1] << endl;
            return 1;
        }
    } else {
        cerr << "error: unable to open file " << argv[1] << endl;
        return 1;
    }
}