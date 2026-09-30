def other():
    for i in range(N):
        if positions[i]: continue
        if i != 0: positions[i] = positions[i-1]
        else:
            j = 1
            while positions[j] == 0:
                j += 1
            positions[i] = positions[j]
    return positions
 
N = int(input())
 
a = input()
b = input()
c = input()
 
a_correct = []
b_correct = []
both_correct = []
possible = True
positions = [0] * N
 
for i in range(N):
    a_correct.append(a[i] == c[i])
    b_correct.append(b[i] == c[i])
    both_correct.append(a_correct[-1] and b_correct[-1])
    if not(a_correct[-1]) and not(b_correct[-1]):
        possible = False
    if a_correct[-1] and not b_correct[-1]:
        positions[i] = 1
    elif b_correct[-1] and not a_correct[-1]:
        positions[i] = 2
 
if not possible:
    print('PLAN FOILED')
else:
    positions = other()
    print('SUCCESS')
    
    cached_pos = -1
    steps = -1
    for i in range(N):
        if positions[i] != cached_pos:
            steps += 1
            cached_pos = positions[i]
 
    print(steps)
