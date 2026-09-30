inputFile = open("sitin.txt", "r")
rows, seatsPerRow = map(int, inputFile.readline().split())
people = int(inputFile.readline())
if rows*seatsPerRow >= people:
    sitting = people
    standing = 0
else:
    sitting = rows*seatsPerRow
    standing = people-sitting
outputFile = open("sitout.txt", "w")
outputFile.write(str(sitting)+" "+str(standing)+"\n")
