import sys
from numpy import random, sqrt

n = int(sys.argv[1])
max = 1000/sqrt(2) # square size, so max_edge = 1000
try:
    max = int(sys.argv[2]/sqrt(2))
except:
    pass

print(n)

coords = random.rand(n,2)*max

for i in range(n):
    for j in range(i+1,n):
        print(int(sqrt(pow(coords[i][0]-coords[j][0],2)+pow(coords[i][1]-coords[j][1],2))), end=" ")
    print()
