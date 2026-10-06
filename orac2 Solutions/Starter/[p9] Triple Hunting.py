rawinput = open('tripin.txt', 'r').readlines()
n = int(rawinput[0])
numbers = list(map(int, rawinput[1:]))
 
rawk = []
for i in range(len(numbers)):
    if numbers[i] % 3 == 0:
        rawk.append(str(i+1))
 
output = ''
if rawk != []:
    output += (f'{len(rawk)}\n')
    output += (' '.join(rawk))
else:
    output = 'Nothing here!'
 
output_file = open('tripout.txt', 'w')
output_file.write(output)
output_file.close()
