l, x, y = map(int, open('piratein.txt', 'r').readlines())
 
output = min(x+y, (2*l)-x-y)
 
output_file = open('pirateout.txt', 'w')
output_file.write(str(output))
output_file.close()
