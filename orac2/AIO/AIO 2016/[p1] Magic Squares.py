A, B, C = map(int, input().split())
square = [[A, B, -1], [C, -1, -1], [-1, -1, -1]]
 
# Do the given rows for >= 1
if B > C:
    square[0][2] = 1
    square[2][0] = 1 + abs(B-C)
    square[2][1] = 1
    square[1][2] = 1 + abs(B-C)
elif C > B:
    square[2][0] = 1
    square[0][2] = 1 + abs(B-C)
    square[1][2] = 1
    square[2][1] = 1 + abs(B-C)
elif C == B:
    square[0][2] = 1
    square[2][0] = 1
    square[1][2] = 1
    square[2][1] = 1
 
# Do 2 remaining ones
sum3 = sum(square[0])
square[2][2] = sum3 - square[2][0] - square[2][1]
square[1][1] = sum3 - square[1][0] - square[1][2]
 
# Do adding a bunch
if square[1][1] <= 0 or square[2][2] <= 0:
    need_to_add = min(square[1][1], square[2][2]) + 1
    square[2][2] += need_to_add
    square[1][1] += need_to_add
    square[0][0] += need_to_add
 
for i in square:
    print(*i)
