N, A, B = map(int, input().split())
 
INF = 10**11
x = 10**7
 
# Maximum possible
 
r1_xplus1s = A - 1
r1_zeroes = N - A
 
r2_xplus1s = B - 1
r2_zeroes = N - B
 
max_answer = N - r2_zeroes - r1_zeroes
 
# Minimum possible
 
r1_infs = A - 1
r2_infs = B - 1
 
min_answer = r1_infs + r2_infs
 
print(max(max_answer - 1, 0) + 1, min(min_answer, N - 1) + 1)
