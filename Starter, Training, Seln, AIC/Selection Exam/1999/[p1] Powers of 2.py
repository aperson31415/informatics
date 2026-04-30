input = open("pow2in.txt", "r").readline
print = open("pow2out.txt", "w").write
 
target = input().strip()
 
for i in range(10000):
    s = str(1 << i)
    if target in s:
        print(str(i)+"\n")
        break
else:
    print("No solution found\n")