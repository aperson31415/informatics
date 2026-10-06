N, K, X = map(int, input().split())
H = list(map(int, input().split()))
 
output = 'NO'
finished = False
 
freq_table = dict()
 
for i in range(K, N):
    if H[i] in freq_table:
        freq_table[H[i]] += 1
    else:
        freq_table[H[i]] = 1
 
for start in range(N - K):
    if H[start] + X in freq_table or H[start] - X in freq_table:
        output = 'YES'
        break
    freq_table[H[start + K]] -= 1
    if freq_table[H[start + K]] == 0:
        del freq_table[H[start + K]]
 
print(output)
