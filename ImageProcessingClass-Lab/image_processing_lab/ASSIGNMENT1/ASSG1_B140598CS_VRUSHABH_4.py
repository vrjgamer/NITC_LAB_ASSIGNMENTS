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

#to find inverse Fourier Transform
def inverseFourierTransform(f, N):
	result = np.zeros(N)
	for i in range(0, N):
		sum = 0
		for h in range(0, N):
			sum = sum + (f[h] * cmath.exp((1j)*((2 * cmath.pi * i * h)/N))) #finding sum of F(u)*e^(j*2*pi*x*u/N)
		else:
			result[i] = sum		
	return result;
	
# main program
def main():
	N = int(input("Enter a N: ")) # get value of N
	M = int(input("Enter a M: ")) # get value of M

	length = N + M - 1 #calculate of length of the convoluted output 

	f = np.zeros(length) # create an array of length
	g = np.zeros(length) # create an array of length
	 
	for i in range(0, N):
			f[i] = int(input("Enter 'f' sequence entry: ")) # get N values for array "f"

	for i in range(0, M):
			g[i] = int(input("Enter 'g' sequence entry: ")) # get M values for array "g"
	 

	F = fourierTransform(f, length) # find Fourier Transform of function F
	G = fourierTransform(g, length) # find Fourier Transform of function G

	result = np.zeros(length) # create an array of length 

	for i in range(0, length):
		result[i] = F[i] * G[i] #convoluting functions of F and G
		
	result = inverseFourierTransform(result, length) # find inverse Fourier Transform

	print "Convoluted output: ",result # output final output

	return

main() #call the main function



#author Vrushbah