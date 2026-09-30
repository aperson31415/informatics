import sys
input = sys.stdin.readline; _write = sys.stdout.write
def print(*args, sep:str=' ', end:str='\n'):
    _write(sep.join(map(str, args)) + end)
 
persona_visits = int(input())
persona_start, persona_end = [], []
for _ in range(persona_visits): a, b = map(int, input().split()); persona_start.append(a); persona_end.append(b)
 
personb_visits = int(input())
personb_start, personb_end = [], []
for _ in range(personb_visits): a, b = map(int, input().split()); personb_start.append(a); personb_end.append(b)
 
minutes = 0
 
a = 0
b = 0
while a < persona_visits and b < personb_visits:
    while personb_end[b] <= persona_start[a]:
        # b << a
        b += 1
        if b >= personb_visits:
            print(minutes)
            exit()
    
    while persona_end[a] <= personb_start[b]:
        # a << b
        a += 1
        if a >= persona_visits:
            print(minutes)
            exit()
    
    if persona_end[a] < personb_end[b] and persona_start[a] < personb_start[b]:
        # a < b
        minutes += max(persona_end[a] - personb_start[b], 0)
    elif personb_end[b] < persona_end[a] and personb_start[b] < persona_start[a]:
        # b < a
        minutes += max(personb_end[b] - persona_start[a], 0)
    elif persona_start[a] >= personb_start[b] and persona_end[a] <= personb_end[b]:
        # a in b
        minutes += max(persona_end[a] - persona_start[a], 0)
    elif personb_start[b] >= persona_start[a] and personb_end[b] <= persona_end[a]:
        # b in a
        minutes += max(personb_end[b] - personb_start[b], 0)
    
    if a == persona_visits - 1 and b == personb_visits - 1: break
    elif a == persona_visits - 1: b += 1
    elif b == personb_visits - 1: a += 1
    else:
        if persona_start[a + 1] <= personb_start[b + 1]:
            a += 1
        else:
            b += 1
 
print(minutes)
