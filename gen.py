import sys
from random import random, randint
from math import sqrt

tab = []
coords = []

n = int(sys.argv[1])
max = 1000
try:
    max = int(sys.argv[2])
except:
    pass

print(n)
for i in range(n):
    tab.append([])
    coords.append([random()*max, random()*max])

for i in range(n):
    tab[i].append(0)
    for j in range(i+1,n):
        x = int(sqrt(pow(coords[i][0]-coords[j][0],2)+pow(coords[i][1]-coords[j][1],2)))
        tab[i].append(x)
        tab[j].append(x)

for i in range(n):
    for j in range(n):
        print(tab[i][j], end=" ")
    print()
