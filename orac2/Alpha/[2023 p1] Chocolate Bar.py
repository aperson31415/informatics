N = int(input())
a = list(map(int, input().split()))
 
block1 = 0
block2 = sum(a)-a[0]
 
min_distance = float('inf')
 
for i in range(N - 1):
    block1 += a[i]
    if i != 0:
        block2 -= a[i]
    current_dist = abs(block2 - block1)
    if current_dist < min_distance:
        min_distance = current_dist
 
print(min_distance)
