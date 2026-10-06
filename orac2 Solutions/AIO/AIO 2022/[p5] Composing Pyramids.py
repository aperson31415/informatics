n = int(input())
p = list(map(int, input().split()))
 
l = [0] * n
r = [0] * n
lw = {}
rw = {}
 
l[0] = 1
lw[p[0]] = 1
 
for i in range(1, n):
    lw_val = lw.get(p[i] - 1, 0)
    l[i] = lw_val + 1
    lw[p[i]] = l[i]
 
r[-1] = 1
rw[p[-1]] = 1
 
for i in range(n - 2, -1, -1):
    rw_val = rw.get(p[i] - 1, 0)
    r[i] = rw_val + 1
    rw[p[i]] = r[i]
 
maxlength = 0
for i in range(n):
    length = min(l[i], r[i])
    if length > maxlength:
        maxlength = length
 
ans = n - (maxlength * 2) + 1
print(ans)
