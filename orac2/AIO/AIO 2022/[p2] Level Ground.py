input_file = open('groundin.txt', 'r')
N = int(input_file.readline())
A = list(map(int, input_file.readline().split()))
A.append('-1')
 
current_max = 0
current = 0
times = 0
for i in A:
    if i == current:
        times += 1
    else:
        if current * times > current_max:
            current_max = current * times
        current = i
        times = 1
 
output_file = open('groundout.txt', 'w')
output_file.write(str(current_max))
output_file.close()
