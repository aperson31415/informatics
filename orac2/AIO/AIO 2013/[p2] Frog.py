 N = int(input())
heights = [int(input()) for _ in range(N)]
 
# Calculate smallest to left and smallest to right arrays
 
smallest_to_left = [heights[0]]
for i in range(1, N): smallest_to_left.append(min(smallest_to_left[-1], heights[i]))
 
smallest_to_right = [heights[-1]]
for i in (range(1, N)[::-1]): smallest_to_right.append(min(smallest_to_right[-1], heights[i]))
smallest_to_right = smallest_to_right[::-1]
 
max_diff = -1
for middle in range(1, N - 1):
    # Find smallest to left and smallest to right
    min_left = smallest_to_left[middle - 1]
    min_right = smallest_to_right[middle]
 
    if min_left < heights[middle] and min_right < heights[middle]:
        curr_diff = (heights[middle] - min_left) + (heights[middle] - min_right)
        max_diff = max(max_diff, curr_diff)
 
print(max_diff)
