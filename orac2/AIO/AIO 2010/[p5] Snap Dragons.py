# Input
R, S = map(int, input().split())
r_cards = [int(input()) for _ in range(R)]
s_cards = [int(input()) for _ in range(S)]
 
# Calculate occurences
r_occurences = dict()
s_occurences = dict()
 
for card in r_cards:
    if card in r_occurences:
        r_occurences[card] += 1
    else:
        r_occurences[card] = 1
 
for card in s_cards:
    if card in s_occurences:
        s_occurences[card] += 1
    else:
        s_occurences[card] = 1
 
# Calculate multiples (r_occ*s_occ)
snap_pairs = 0
 
for card in r_occurences:
    if card in s_occurences:
        # Both have it, so can calculate
        snap_pairs += r_occurences[card]*s_occurences[card]
 
print(snap_pairs)
