import sys
from numpy import random

n = int(sys.argv[1])
max = 1000
try:
    max = int(sys.argv[2])
except:
    pass

order = random.permutation(range(n))
tab = [[0]*n for i in range(n)]
size = 0

print(n)
for i in range(n):
    if size == 0:
        size = min(int(random.exponential()+3),n-i)
    for j in range(i+1,i+size):
        edge = random.randint(3*max/4,max)
        tab[order[i]][order[j]] = edge
        tab[order[j]][order[i]] = edge
    size -= 1

for i in range(n):
    for j in range(i+1,n):
        if tab[i][j] == 0:
            tab[i][j] = random.randint(0,max/4)
        print(tab[i][j], end=" ")
    print()
