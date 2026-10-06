input_file = open('melodyin.txt', 'r').readlines()
N, K = list(map(int, input_file[0].split()))
S = list(map(int, input_file[1:]))
 
frequencies = {n:{} for n in range(3)}
need_to_change = 0
 
for i in range(len(S)):
    if S[i] in frequencies[i%3]:
        frequencies[i%3][S[i]] += 1
    else:
        frequencies[i%3][S[i]] = 1
 
for i in range(3):
    most_occurences = max(frequencies[i].values())
    total_values = sum(frequencies[i].values())
    need_to_change += total_values - most_occurences
 
output_file = open('melodyout.txt', 'w')
output_file.write(str(need_to_change))
output_file.close()
