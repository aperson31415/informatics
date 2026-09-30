input_file = open('bookin.txt', 'r')
N = int(input_file.readline())
word = input_file.readline()
 
output = 0
current_letter = ''
score = 0
 
for i in range(len(word)):
    #print(current_letter, word[i], score, output)
    if word[i] == current_letter or word[i] == '?':
        score += 1
    else:
        output += score
        score = 0
        current_letter = word[i]
output += score
 
output_file = open('bookout.txt', 'w')
output_file.write(str(output))
output_file.close()
