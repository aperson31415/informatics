original_fruits = int(open('taktakin.txt', 'r').read())
 
pattern = [2, 4, 8, 5, 10, 9, 7, 3, 6, 1]
remainder = original_fruits % 11
index = pattern.index(remainder)
 
doubles = 9-index
end_fruits = original_fruits*(2**doubles)
 
output_file = open('taktakout.txt', 'w')
output_file.write(f'{doubles} {end_fruits}')
output_file.close()
