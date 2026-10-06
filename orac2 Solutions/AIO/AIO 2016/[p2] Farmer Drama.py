N = int(input())
w = list(map(int, input().split()))
 
# Calculate the fence positions
land_area = sum(w)
middle = land_area/2
 
fence_pos = []
current_index = 0
for i in w[:-1]:
    current_index += i
    fence_pos.append(current_index)
 
# Calculate distances from centre
distances = []
for i in fence_pos:
    distances.append(abs(middle-i))
 
# Get 'sides'
left_dist = set()
right_dist = set()
for i in range(len(distances)):
    if fence_pos[i] > middle:
        right_dist.add(distances[i])
    elif fence_pos[i] < middle:
        left_dist.add(distances[i])
 
# Calculate which ones are not in pairs
result = 0
 
for i in left_dist:
    if not i in right_dist:
        result += 1
 
for i in right_dist:
    if not i in left_dist:
        result += 1
 
print(result)
