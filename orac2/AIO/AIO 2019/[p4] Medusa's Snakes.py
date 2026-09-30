import sys
input = sys.stdin.readline; _write = sys.stdout.write
def print(*args, sep:str=' ', end:str='\n'):
    _write(sep.join(map(str, args)) + end)
 
N = int(input())
dna = input()
 
def find_char(A, start, char, times, length):
    last_index = -1
    start -= 1
    for i in range(times):
        while True:
            start += 1
            if start >= length: return -1
            if A[start] == char: break
 
    return start
 
def check(dna, N, venom_test):
    start = 0
    start = find_char(dna, start, "S", venom_test, N)
    if start == -1: return False
    start = find_char(dna, start, "N", venom_test, N)
    if start == -1: return False
    start = find_char(dna, start, "A", venom_test, N)
    if start == -1: return False
    start = find_char(dna, start, "K", venom_test, N)
    if start == -1: return False
    start = find_char(dna, start, "E", venom_test, N)
    if start == -1: return False
    return True
 
lo = 0
hi = N
 
while lo != hi:
    mid = (lo+hi+1)//2
 
    if check(dna, N, mid):
        lo = mid
    else:
        hi = mid-1
 
print(lo)
