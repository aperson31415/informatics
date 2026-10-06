input_file = open('telein.txt', 'r')
N = int(input_file.readline())
I = input_file.readline()
 
pos = 0
visited = {0}
Visited = 1
for i in I:
    if i == 'L':
        pos -= 1
    elif i == 'R':
        pos += 1
    elif i == 'T':
        pos = 0
    visited.add(pos)
 
output_file = open('teleout.txt', 'w')
output_file.write(str(len(visited)))
output_file.close()
