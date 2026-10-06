inputFile = open("addin.txt", "r")
a,b = map(int, inputFile.readline().split())
total = a+b
outputFile = open("addout.txt", "w")
outputFile.write(str(total)+'\n')
inputFile.close()
outputFile.close()
