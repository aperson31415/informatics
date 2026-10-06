N = int(input())
daisies = [int(input()) for _ in range(3)]
daisies.sort()
 
# Capture from both sides
test1 = daisies[2] - daisies[0] + 1
 
# 2Right-capture
test2 = (daisies[1] - daisies[0] + 1) + (N - daisies[2] + 1)
 
# 2Left-capture
test3 = (daisies[2] - daisies[1] + 1) + (daisies[0])
 
# 1Right-capture
test4 = (N - daisies[1] + 1) + 1
 
# 1Left-capture
test5 = (daisies[1]) + 1
 
print(N - min(test1, test2, test3, test4, test5))
