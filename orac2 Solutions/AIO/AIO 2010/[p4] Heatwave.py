N, H = map(int, input().split())
T = [int(input()) for _ in range(N)]
for i in range(N):
    T[i] = int(T[i] >= H)
 
current = 0
max_value = -1
for i in range(N):
    if T[i] == 1:
        current += 1
    else:
        if current > max_value:
            max_value = current
        current = 0
 
if current > max_value:
    max_value = current
 
print(max_value)
Test Results
