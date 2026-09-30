N, M = map(int, input().split())
red = {1}
blue = {2}
tags = [input() for _ in range(M)]
 
for tag in tags:
    tagger, victim = map(int, tag.split())
    if tagger in red:
        red.add(victim)
    elif tagger in blue:
        blue.add(victim)
    else:
        print(f'Unknown {tagger}, {type(tagger)}')
 
print(f'{len(red)} {len(blue)}')
