numbersraw = open("dishin.txt", "r").readlines()
numbers = list(map(int, numbersraw))
 
maximum = 0
minimum = 1000001
total = 0
 
for i in range(len(numbers)-1):
    I = numbers[i+1]
    total += I
    if I > maximum:
        maximum = I
    if I < minimum:
        minimum = I
 
rawmean = (total/numbers[0])
mean = rawmean-(rawmean%1)
 
output_file = open('dishout.txt', 'w')
output_file.write(f'{minimum} {maximum} {int(mean)}')
output_file.close()
