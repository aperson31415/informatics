rawinput = open('robotin.txt', 'r')
K = int(rawinput.readline())
I = rawinput.readline()
 
x = 0
y = 0
for i in I:
    if i == 'N':
        y += 1
    elif i == 'E':
        x += 1
    elif i == 'S':
        y -= 1
    elif i == 'W':
        x -= 1
 
output_file = open('robotout.txt', 'w')
output_file.write(f'{abs(x)+abs(y)}')
output_file.close()
