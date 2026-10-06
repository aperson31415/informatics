N, K = map(int, input().split())
distances = [int(input()) for _ in range(N - 1)]
Kdistances = list()
 
currentsum = sum(distances[:K])
Kdistances.append(currentsum)
 
for i in range(N - K - 1):
    currentsum -= distances[i]
    currentsum += distances[K + i]
    Kdistances.append(currentsum)
 
print(min(Kdistances))
