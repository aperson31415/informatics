n = int(open('vasesin.txt', 'r').readline())
 
if n < 6:
    output = [0, 0, 0]
else:
    output = [1, 2, n-3]
 
output_file = open('vasesout.txt', 'w')
output_file.write(' '.join(map(str, output)))
output_file.close()
