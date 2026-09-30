R, C, rROSE, cROSE, rSCARLET, cSCARLET = map(int, input().split())
 
distance = abs(rROSE-rSCARLET) + abs(cROSE-cSCARLET)
if distance % 2 == 1:
    print('ROSE')
else:
    print('SCARLET')
