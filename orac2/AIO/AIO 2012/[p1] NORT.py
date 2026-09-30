w, h = map(int, open('nortin.txt', 'r').readline().split())
 
score = (w*h) - ((w*h) % 2)
 
output_file = open('nortout.txt', 'w')
output_file.write(str(score))
output_file.close()
