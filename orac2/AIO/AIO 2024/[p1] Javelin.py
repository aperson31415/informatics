input_file = open('javelin.txt', 'r')
N = int(input_file.readline())
D = map(int, input_file.readline().split())
 
leader = 0
leaders = 0
for i in D:
    if i > leader:
        leader = i
        leaders += 1
 
output_file = open('javelout.txt', 'w')
output_file.write(str(leaders))
output_file.close()
