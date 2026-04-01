from math import sqrt, ceil
 
people, problems = map(int, input().split())
 
cycles = ceil((sqrt(1 + 8*problems) - 1) / 2) # Rounds of solving
full_cycles = cycles//people # Amount everyone's done
last_amount = (problems - cycles*(cycles-1)//2)
if last_amount != 0 and cycles % people == 0: full_cycles -= 1
 
# Check last person
lastid = cycles % people
if lastid == 0: lastid = people
last_person = people*full_cycles*(full_cycles-1)//2 + (lastid)*full_cycles + last_amount
 
# Check 2nd last person
last2person = people*full_cycles*(full_cycles-1)//2 + ((lastid-1)%people)*full_cycles + cycles-1
 
# Output
if last2person > last_person:
    if (lastid-1)%people == 0:
        lastid = people
    else:
        lastid = (lastid-1)%people
    print(lastid, last2person)
elif last2person < last_person:
    if lastid == 0: lastid = people
    print(lastid, last_person)
else:
    first = people if (lastid-1)%people == 0 else (lastid-1)%people 
    print(min(first, lastid), last_person)