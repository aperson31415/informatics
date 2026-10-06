raw_xy = [tuple(map(int, input().split())) for _ in range(8)]
 
x = []
y = []
for xy_pair in raw_xy:
    x.append(xy_pair[0])
    y.append(xy_pair[1])
 
'''
corners are points on outside of rectangle (actual corners)
(From left to right, top to bottom)
 
next are edge values (x or y)
'''
 
# Get corner points
corners = set([(min(x), max(y)), (max(y), max(x)), (min(y), min(x)), (max(y), min(x))])
 
# Get edges
left = min(x)
right = max(x)
top = max(y)
bottom = min(y)
 
# Test for '4 point thingies' (will be 3)
if x.count(left) == 4:
    output = 'W'
elif x.count(right) == 4:
    output = 'E'
elif y.count(top) == 4:
    output = 'N'
elif y.count(bottom) == 4:
    output = 'S'
 
print(output)
