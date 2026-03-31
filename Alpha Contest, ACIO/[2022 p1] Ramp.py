N = int(input())
d = list(map(int, input().split()))
 
maximum = 1
current = 0
previous = -1
 
for i in range(N):
    if i == 0:
        previous = d[i]
        current += 1
        continue
    if d[i] == previous+1:
        current += 1
        if current > maximum:
            maximum = current
    else:
        current = 1
    previous = d[i]
 
if current > maximum:
    maximum = current
 
print(maximum)
