rawinput = open('artin.txt', 'r').readlines()
N = int(rawinput[0])
H = rawinput[1:]
 
maxx = 0
minx = 100001
maxy = 0
miny = 100001
 
for i in H:
    x, y = map(int, i.split())
    if x > maxx:
        maxx = x
    if x < minx:
        minx = x
    if y > maxy:
        maxy = y
    if y < miny:
        miny = y
 
output_file = open('artout.txt', 'w')
output_file.write(str((maxx-minx)*(maxy-miny)))
output_file.close()
