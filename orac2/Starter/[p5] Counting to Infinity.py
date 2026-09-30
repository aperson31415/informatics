fileIn = open("countin.txt", "r")
number = int(fileIn.read())
fileOut = open("countout.txt", "w")
for i in range(number):
    fileOut.write(str(i+1)+'\n')
fileIn.close()
fileOut.close()
