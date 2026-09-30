N = int(input())
H = list(map(int, input().split()))
 
# Get differences
 
differences = []
for i in range(N-1):
    differences.append(H[i+1]-H[i])
 
#print('diff', differences)
 
# Run main loop
 
max_optimisation = 0
 
for i in range(1, N-1):
    left = differences[i-1]
    right = differences[i]
    if left == abs(left) and right != abs(right) or \
       left != abs(left) and right == abs(right):
        # If 1 is positive, and other is negative (means u can optimise)
        optimisation = min(abs(left), abs(right)) * 2
        if optimisation > max_optimisation:
            max_optimisation = optimisation
 
# Calculate original ugliness and subtract optimisation
for i in range(N-1):
    differences[i] = abs(differences[i])
 
# Consider Edges
if max_optimisation < differences[0]:
    max_optimisation = differences[0]
 
if max_optimisation < differences[-1]:
    max_optimisation = differences[-1]
 
# Output
 
print(sum(differences) - max_optimisation)
