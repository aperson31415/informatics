def bsearch(A, x): # Copied off orac
    lo = 0
    hi = len(A)-1
    while lo != hi:
        mid = (lo+hi)//2
        if A[mid] >= x:
            hi = mid
        else:
            lo = mid+1
        
    # Check that the value exists
    if A[lo] >= x:
        return A[lo]
    else:
        return -1
 
bids = [int(input()) for _ in range(13)]
 
max_score = 0
 
def search(n):
    score = 0
    cards_left = [i for i in range(1, 14)] # probably could have used more efficient data structure tho
 
    for i in range(n)[::-1]:
        val = bsearch(cards_left, bids[i])
        if val == -1:
            # use up lowest
            cards_left.remove(min(cards_left))
            score -= (i+1)
        elif val == bids[i]:
            val2 = bsearch(cards_left, bids[i] + 1)
            if val2 != -1:
                cards_left.remove(val2)
                score += (i+1)
            else:
                cards_left.remove(val)
        elif val > bids[i]:
            score += (i+1)
            cards_left.remove(val)
    
    for i in range(n, 13)[::-1]:
        val = bsearch(cards_left, bids[i])
        if val == -1:
            # use up lowest
            cards_left.remove(min(cards_left))
            score -= (i+1)
        elif val == bids[i]:
            val2 = bsearch(cards_left, bids[i] + 1)
            if val2 != -1:
                cards_left.remove(val2)
                score += (i+1)
            else:
                cards_left.remove(val)
        elif val > bids[i]:
            score += (i+1)
            cards_left.remove(val)
    return score
 
for i in range(13):
    if search(i) > max_score:
        max_score = search(i)
 
print(max_score)
