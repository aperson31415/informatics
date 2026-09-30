D, T = map(int, input().split())
throws = [input().split() for _ in range(T)]
 
recieved = dict()
answer = 0
 
for i in range(T):
    value = throws[i][0]
    if value in recieved:
        if recieved[value] > 0:
            recieved[value] -= 1
        else:
            answer += 1
    else:
        answer += 1
    if throws[i][1] in recieved:
        recieved[ throws[i][1] ] += 1
    else:
        recieved[ throws[i][1] ] = 1
 
print(str(answer))
