N, L = map(int, input().split())
P = list(map(int, input().split()))
 
# One-way
ans = P[-1]
if L - P[0] < ans:
    ans = L - P[0]
 
# back then forwards
 
for i in range(N - 1):
    t = 2 * P[i] + L - P[i+1]
    if t < ans:
        ans = t
 
# other way around
for i in range(1, N):
    t = 2 * (L - P[i]) + P[i - 1]
    if t < ans:
        ans = t
 
print(ans)
