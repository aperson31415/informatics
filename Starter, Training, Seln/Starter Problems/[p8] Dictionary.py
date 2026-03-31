rawinput = open('dictin.txt', 'r').readlines()
d, w = map(int, rawinput[0].split())
 
rawwords = rawinput[1:d+1]
x = rawinput[d+1:]
 
'''line1 = input()
d, w = map(int, line1.split())
rawwords = [input() for i in range(d)]
x = [int(input()) for i in range(w)]'''
 
words = {}
for i in rawwords:
    a, b = map(int, i.split())
    words[a] = b
 
output = []
for i in x:
    if int(i) in words:
        output.append(str(words[int(i)]))
    else:
        output.append('C?')
 
output_file = open('dictout.txt', 'w')
output_file.write('\n'.join(output))
output_file.close()
