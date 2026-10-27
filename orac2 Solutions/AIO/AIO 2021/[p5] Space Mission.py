 N, F = map(int, input().strip().split())
C = [int(input().strip()) for i in range(N)]
 
starts = []
ends = []
 
# Find valid starting points
for i, val in enumerate(C):
    if not starts or val < starts[-1][0]:
        starts.append((val, i))
 
# Find valid ending points
for i, val in reversed(list(enumerate(C))):
    if not ends or val < ends[-1][0]:
        ends.append((val, i))
 
ends = ends[::-1]
 
ans = -1
prev_start = 0
 
for val, i in ends:
    # Update the position of the "best starting point"
    while prev_start < len(starts) and val + starts[prev_start][0] > F:
        prev_start = prev_start + 1
 
    # If the output is a valid mission, record its length in the answer
    if prev_start < len(starts) and val + starts[prev_start][0] <= F:
        ans = max(ans, i - starts[prev_start][1] + 1)
 
# We cannot launch and exit on the same day
if ans == 1:
    ans = -1
 
print(ans)
