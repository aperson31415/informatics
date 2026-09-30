N = int(input())
a = list(map(int, input().split()))
 
start = dict()
end = dict()
 
# Build end
 
for i in range(N):
    if a[i] in end:
        end[a[i]] += 1
    else:
        end[a[i]] = 1
 
# Build start
start_delicious = 0
end_delicious = len(end.keys())
 
max_delicious = 2
 
for i in range(N):
    end[a[i]] -= 1
    if end[a[i]] == 0:
        end_delicious -= 1
    if a[i] in start:
        start[a[i]] += 1
    else:
        start[a[i]] = 1
        start_delicious += 1
    if start_delicious + end_delicious > max_delicious:
        max_delicious = start_delicious + end_delicious
 
print(max_delicious)
