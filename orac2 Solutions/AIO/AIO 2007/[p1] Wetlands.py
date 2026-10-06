L = list(map(int, open('wetin.txt', 'r').readlines()))
 
current = 0
for i in L:
    current += i
    if current >= 10:
        current -= 10
    else:
        current = 0
 
output_file = open('wetout.txt', 'w')
output_file.write(str(current))
output_file.close()
