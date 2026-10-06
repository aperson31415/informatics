input_file = open('shopin.txt', 'r')
N, K = map(int, input_file.readline().split())
C = list(map(int, input_file.readline().split()))
 
discounted = sum(C[:K])
other = sum(C[K+1:N-K:2])
 
output_file = open('shopout.txt', 'w')
output_file.write(str(discounted+other))
output_file.close()
