rawinput = open('cavalryin.txt', 'r').readlines()
N = int(rawinput[0])
A = map(int, rawinput[1:])
 
B = {}
for i in A:
    if not (i in B):
        B[i] = 0
    B[i] += 1
 
for i in B:
    if B[i] % i == 0:
        c = "YES"
    else:
        c = "NO"
        break
 
output_file = open('cavalryout.txt', 'w')
output_file.write(c)
output_file.close()
