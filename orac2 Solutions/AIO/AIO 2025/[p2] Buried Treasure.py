N, L = map(int, input().split())
A = []; B = []
 
for i in range(N):
    appA, appB = map(int, input().split())
    A.append(appA); B.append(appB);
 
# Run the program
top = float('inf')
bottom = -1
 
for i in range(N):
    if A[i] > bottom:
        bottom = A[i]
    if B[i] < top:
        top = B[i]
 
if top - bottom >= 0:
    print(top - bottom + 1)
else:
    print(0)
