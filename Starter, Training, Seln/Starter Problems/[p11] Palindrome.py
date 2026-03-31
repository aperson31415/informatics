rawinput = open('palin.txt', 'r')
N = int(rawinput.readline())
word = list(rawinput.readline().strip())
'''
N = int(input())
word = list(input())
'''
 
toChange = {}
 
for i in range(N//2):
    if not (word[i] == word[len(word)-i-1]):
        toChange[i] = list(word[i]+word[len(word)-i-1])
 
for i in toChange:
    correct_letter = min(toChange[i])
    raw_index = toChange[i].index(correct_letter)
    if raw_index == 0:
        correct_index = i
    else:
        correct_index = len(word)-i - 1
    changed_index = N - correct_index - 1
    word[changed_index] = correct_letter
    #print(toChange[i],'.',raw_index,'->',correct_index,'->',changed_index,'->',correct_letter,word)
 
#print(''.join(word))
output_file = open('palout.txt', 'w')
output_file.write(''.join(word))
output_file.close()
