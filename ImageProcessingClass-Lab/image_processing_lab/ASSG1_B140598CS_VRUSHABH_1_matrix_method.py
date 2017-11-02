from PIL import Image as IMG
import numpy  as np

def createBoxMatrix(f, g, N):
	result = np.zeros((N,N))
	
	for i in range(0, N):
		for j in range(0, N):
			result[i, j] = f[i] * g[j]

	return result;


N = int(input("Enter a N: "))
f = np.zeros(N)
g = np.zeros(N)
 
for i in range(0, N):
		f[i] = int(input("Enter entry: "))

for i in range(0, N):
		g[i] = int(input("Enter entry: "))
 

temp = createBoxMatrix(f, g, N)

print temp

length = N + N - 1

result = np.zeros(length)


for i in range(0, length):
	start = 0
	if(i < N):
		start = 0
	else:
		start = i - N + 1
	
	for j in range(start, i - start + 1):
		result[i] += temp[j][i - j]

print "Convoluted output: ",result






#author Vrushbabh
	 