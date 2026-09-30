import sys
 
sys.stdin = open("spiesin.txt", "r")
sys.stdout = open("spiesout.txt", "w")
 
def median(A:list):
    if len(A) % 2 == 1: return A[(len(A)+1)//2 - 1]
    else: return (A[len(A)//2 - 1] + A[len(A)//2])//2
 
n = int(input())
x, y = [], []
for _ in range(n): 
    xi, yi = map(int, input().split())
    x.append(xi)
    y.append(yi)
 
x.sort()
y.sort()
 
print(median(x), median(y))
