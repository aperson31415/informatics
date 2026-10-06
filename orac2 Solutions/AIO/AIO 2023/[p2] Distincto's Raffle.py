input_file = open('rafflein.txt', 'r')
 
N, K = map(int, input_file.readline().split())
I = map(int, input_file.readline().split())
 
frequencies = {}
for i in I:
    if i in frequencies:
        frequencies[i] += 1
    else:
        frequencies[i] = 1
 
leftovers = []
for i in frequencies:
    if frequencies[i] == 1:
        leftovers.append(i)
 
if leftovers != []:
    output = min(leftovers)
else:
    output = -1
 
output_file = open('raffleout.txt', 'w')
output_file.write(str(output))
output_file.close()
