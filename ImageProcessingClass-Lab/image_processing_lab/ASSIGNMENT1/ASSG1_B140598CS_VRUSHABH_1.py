from PIL import Image as IMG
import numpy  as np
import cmath

# to find Fourier Transform 
def fourierTransform(f, N):
	result = np.zeros(N)
	for i in range(0, N):
		sum = 0
		for h in range(0, N):
			sum = sum + (f[h] * cmath.exp((-1j)*((2 * cmath.pi * i * h)/N))) #finding sum of f(x)*e^(-j*2*pi*x*u/N)
		else:
			result[i] = sum		
	return result;

# to find inverse Fourier Transform 
def inverseFourierTransform(f, N):
	result = np.zeros(N)
	for i in range(0, N):
		sum = 0
		for h in range(0, N):
			sum = sum + (f[h] * cmath.exp((1j)*((2 * cmath.pi * i * h)/N))) #finding sum of F(u)*e^(j*2*pi*x*u/N)
		else:
			result[i] = sum		
	return result;
	

# main Program
def main():	
	N = int(input("Enter a N: ")) #get N value

	length = N + N + 1 # length of convoluted sequence

	f = np.zeros(length)
	g = np.zeros(length)
	 
	for i in range(0, N):
			f[i] = int(input("Enter 'f' sequence entry: "))

	for i in range(0, N):
			g[i] = int(input("Enter 'g' sequence entry: "))
	 

	F = fourierTransform(f, length)
	G = fourierTransform(g, length) 

	result = np.zeros(length)

	for i in range(0, length):
		result[i] = F[i] * G[i] #convoluting functions
		
	result = inverseFourierTransform(result, length)

	print "Convoluted output: ",result

	return


main() #call main function


#author Vrushbah