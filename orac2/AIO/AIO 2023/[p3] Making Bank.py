N = int(input())
d = input() # Day's actions in string
D = [char for char in d] # Day's actions in list
 
money = 0
s = 1
 
for n in range(len(D)):
    # If no art class
    if D[n] == 'M':
        money += s
    # If class
    elif D[n] == 'C':
        if s + 1 > (len(d) - n):
            money += s # Paint
        elif s + 1 < (len(d) - n):
            s += 1 # Take class
        elif s + 1 == (len(d) - n):
            # Take class and paint yield same results
            s += 1
 
print(money)
