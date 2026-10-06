rawinput = open('ladyin.txt', 'r').readlines()
N = int(rawinput[0])
F = list(map(int, rawinput[1:]))
 
output = max(F)-min(F)+1
 
output_file = open('ladyout.txt', 'w')
output_file.write(str(output))
output_file.close()
