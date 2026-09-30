n, m = map(int, input().split())
houses = [int(input()) for i in range(n)]
 
current = 0
current_max = -1
 
# Get first sum
for i in range(m):
    current += houses[i]
 
if current > current_max:
    current_max = current
 
# Calculate the rest of the sums
for i in range( len(houses) - m ):
    # Remove the first #of people
    current -= houses[i]
    # Add to the end
    current += houses[m+i]
 
    if current > current_max:
        current_max = current
 
print(current_max)
