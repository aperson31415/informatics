N, K = map(int, input().split())
 
freq_table = dict()
current_max = 1
 
for _ in range(N):
    x, t = map(int, input().split())
    current_data = (x*K)-t
    if current_data in freq_table:
        freq_table[current_data] += 1
    else:
        freq_table[current_data] = 1
    if freq_table[current_data] > current_max:
        current_max = freq_table[current_data]
 
print(current_max)
