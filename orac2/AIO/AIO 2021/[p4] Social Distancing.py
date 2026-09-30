N, K = map(int, input().split())
D = [int(input()) for _ in range(N)]
D.sort()
 
previous = D[0]
max_hippos = 1
for i in range(1, N):
    if D[i] - previous >= K:
        max_hippos += 1
        previous = D[i]
 
print(max_hippos)
