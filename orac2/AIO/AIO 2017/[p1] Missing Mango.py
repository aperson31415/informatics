ax, bx, ad, bd = map(int, open('manin.txt', 'r').readline().split())
 
if bx+bd == ax-ad or bx+bd == ax+ad:
    distance = bx+bd
elif bx-bd == ax-ad or bx-bd == ax+ad:
    distance = bx-bd
else:
    distance = 'PooPoo'
 
output_file = open('manout.txt', 'w')
output_file.write(str(distance))
output_file.close()
