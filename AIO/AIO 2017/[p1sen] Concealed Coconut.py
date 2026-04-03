from math import sqrt
 
Ix, Iy, Id = map(int, input().split())
Cx, Cy, Cd = map(int, input().split())
 
distance = sqrt(abs(Ix - Cx)**2 + abs(Iy - Cy)**2)
 
if distance <= Id + Cd and distance >= abs(Id - Cd):
    print('yes')
else:
    print('no')
