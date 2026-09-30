N = int(input())
L = list(map(int, input().split()))
R = list(map(int, input().split()))
 
passed = True
current_cost = L[0]
 
for i in range(1, N):
    if current_cost <= L[i]:
        current_cost = L[i]
    elif current_cost > L[i] and current_cost <= R[i]:
        pass
    else:
        passed = False
        break
 
print('YES' if passed else 'NO')
