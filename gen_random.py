import sys
from numpy import random

n = int(sys.argv[1])
max = 1000
try:
    max = int(sys.argv[2])
except:
    pass

print(n)
for i in range(n):
    for j in range(i+1,n):
        print(random.randint(max), end=" ")
    print()
