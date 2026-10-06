import sys
input = sys.stdin.readline; _write = sys.stdout.write
def print(*args, sep:str=' ', end:str='\n'):
    _write(sep.join(map(str, args)) + end)
 
# Get input
d = int(input())
numbers = [int(input()) for _ in range(d)]
seq = 0
length = 1
 
for i in range(1, d):
    if numbers[i] > numbers[i - 1]:
        length += 1
    elif not(numbers[i] > numbers[i-1]) and length >= 2:
        seq += 1
        length = 1
    elif not(numbers[i] > numbers[i - 1]) and length < 2:
        length = 1
    else:
        raise SyntaxError
 
# Check if end
if length >= 2:
    seq += 1
 
print(seq)
