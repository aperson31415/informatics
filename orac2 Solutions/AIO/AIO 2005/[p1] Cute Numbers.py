rawinput = open('cutein.txt', 'r').readlines()
d = int(rawinput[0])
N = list(map(int, rawinput[1:]))
 
count = 0
for i in range(d):
    if N[len(N)-i-1] == 0:
        count += 1
    else:
        break;
 
output_file = open('cuteout.txt', 'w')
output_file.write(str(count))
output_file.close()
