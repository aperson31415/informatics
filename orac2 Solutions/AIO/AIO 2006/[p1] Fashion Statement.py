t = int(open('fashin.txt', 'r').readline())
 
current = t
notes = 0
for i in [100,20,5,1]:
    j = current//i
    notes += j
    current -= j*i
 
output_file = open('fashout.txt', 'w')
output_file.write(str(notes))
output_file.close()
