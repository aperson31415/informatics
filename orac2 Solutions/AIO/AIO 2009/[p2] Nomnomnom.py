N = int(input())
D = [int(input()) for _ in range(N)] # Dishes
 
satisfied = 0
current_max = 0
current_eaten = 0
for dish in D:
    current_eaten += dish
    if current_eaten >= current_max:
        current_max = current_eaten
        current_eaten = 0
        satisfied += 1
 
print(satisfied)
