import bisect
 
n = int(input())
k = int(input())
val = [int(input()) for i in range(n)]
 
pref_sum = [0] * (n + 1)
for i in range(n):
    pref_sum[i + 1] = pref_sum[i] + val[i]
 
left = 0
right = pref_sum[-1]
while left <= right:
    mid = (left + right) // 2
    count = 0
    for i in range(n):
        target = mid + pref_sum[i]
        idx = bisect.bisect_left(pref_sum, target, lo=i + 1)
        count += (n + 1) - idx
    if count >= k:
        left = mid + 1
    else:
        right = mid - 1
 
print(right)
