N = int(input())
goals = list(map(int, input().split()))
 
output = False
 
# Run stimulation
team1 = 0
team2 = 0
 
for i in goals:
    if i == 1:
        team1 += 1
    else:
        team2 += 1
    if team1 > team2:
        output = True
 
# Output
if output:
    print('YES')
else:
    print('NO')
