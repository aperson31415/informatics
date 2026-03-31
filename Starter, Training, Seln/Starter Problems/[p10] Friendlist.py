friendlist = [0] * 1001
 
N = int(input())
listin = [input() for _ in range(N)]
 
for line in listin:
    a,b = line.split()
    friendlist[int(a)] += 1
    friendlist[int(b)] += 1
 
max_friends_num = max(friendlist)
 
for id,val in enumerate(friendlist):
    if val == max_friends_num:
        print(str(id))
