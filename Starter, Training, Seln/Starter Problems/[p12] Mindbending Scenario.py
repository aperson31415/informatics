left1, bottom1, right1, top1 = list(map(int, input().split()))
left2, bottom2, right2, top2 = list(map(int, input().split()))
 
interLeft = max(left1, left2)
interBottom = max(bottom1, bottom2)
interRight = min(right1, right2)
interTop = min(top1, top2)
 
if interLeft < interRight and interBottom < interTop:
    interArea = (interRight - interLeft) * (interTop - interBottom)
else:
    interArea = 0
 
area = ((right1 - left1) * (top1 - bottom1)) + ((right2 - left2) * (top2 - bottom2)) - interArea
 
print(str(area))
