nk = open('ninjain.txt', 'r').readline()
n, k = map(int, nk.split())
 
output = str(n - ( (n+k)//(k+1) ))
 
output_file = open('ninjaout.txt', 'w')
output_file.write(output)
output_file.close()
