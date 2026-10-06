rawinput = open('mixin.txt', 'r').read()
n, d = rawinput.split()
n, d = int(n), int(d)
 
b = n % d
a = int((n-b)/d)
 
output_file = open('mixout.txt', 'w')
if b == 0:
    output_file.write(f'{a}')
else:
    output_file.write(f'{a} {b}/{d}')
output_file.close()
