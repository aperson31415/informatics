total_chairs, friends_no, friends_wet_available = map(int, input().split())
data = str(input())
data = data.replace('w', '1')
data = data.replace('d', '0')
data = list(map(int, data))
 
start = 0
end = friends_no-1
wet_chairs = sum(data[:friends_no])
 
smallest_interval = float('inf')
 
while start < (total_chairs - friends_no + 1) and end < total_chairs:
    while (end - start + 1) - wet_chairs < friends_no - friends_wet_available \
            and end < total_chairs - 1:
        # When dry chairs < people who need dry chairs
        # Automatically at least #friends long interval.
        end += 1
        wet_chairs += data[end]
        #print('Start', start, 'End', end, 'Interval', end - start + 1, 'Wet Chairs', wet_chairs)
 
    #print('Start', start, 'End', end, 'Interval', end - start + 1, 'Wet Chairs', wet_chairs)
 
    if (end - start + 1) < smallest_interval and \
       (end - start + 1) - wet_chairs >= friends_no - friends_wet_available and \
       end - start + 1 >= friends_no:
        # If Interval is smaller than smallest cached interval
        # and Dry chairs >= people who need dry chairs
        smallest_interval = end - start + 1
 
    wet_chairs -= data[start]
    start += 1
 
print(smallest_interval)
