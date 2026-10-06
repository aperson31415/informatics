input_file = open('elecin.txt', 'r')
n = int(input_file.readline())
N = input_file.readline()
 
A, B, C = 0, 0, 0
 
for i in N:
    if i == 'A':
        A += 1
    elif i == 'B':
        B += 1
    elif i == 'C':
        C += 1
 
if A > C and A > B:
    output = 'A'
elif B > C and B > A:
    output = 'B'
elif C > B and C > A:
    output = 'C'
else:
    output = 'T'
 
output_file = open('elecout.txt', 'w')
output_file.write(output)
output_file.close()
