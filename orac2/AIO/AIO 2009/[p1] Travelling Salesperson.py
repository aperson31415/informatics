L = list(map(int, open('salesin.txt', 'r').readlines()))
 
output_file = open('salesout.txt', 'w')
output_file.write(str(int(sum(L)-min(L))))
output_file.close()
