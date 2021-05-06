# Max-TSP approximation algorithms

Compile:

    g++ -I [path to boost] -O3 src/main.cpp src/[algorithm].cpp -o out/[algorithm]

Generate tests:

    python3 gen.py [n] [max_weight (optional)]

Benchmark:

    sh benchmark.sh [test file]
