rawinput = open('encyin.txt', 'r').readlines()
n, q = list(map(int, rawinput[0].split()))
p = list(map(int, rawinput[1:n+1]))
x = list(map(int, rawinput[n+1:]))
 
print(n,q,'\n',p,x)
 
output = []
 
for i in x:
    output.append(p[i-1])
 
print(output)
 
output_file = open('encyout.txt', 'w')
output_file.write('\n'.join(map(str, output)))
output_file.close()
