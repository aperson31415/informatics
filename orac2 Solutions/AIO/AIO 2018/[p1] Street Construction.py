from math import ceil
 
rawinput = open('streetin.txt', 'r').readline()
n, k = map(int, rawinput.split())
 
output = ceil( (n-k)/(k+1) )
 
output_file = open('streetout.txt', 'w')
output_file.write(str(output))
output_file.close()
