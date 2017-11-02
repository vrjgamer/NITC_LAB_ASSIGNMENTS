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

#main program
def main():
	N = int(input("Enter a N: ")) # get value of N
	f = np.zeros(N) # create array of N integers initialized with 0s
	 
	for i in range(0, N):
			f[i] = int(input("Enter 'f' sequence entry: ")) # = get values in the array

	#finding fourierTransform
	F = fourierTransform(f, N)

	print "Fourier output: ",F #output Fourier Transform
	
	return


main() #call main function

#author Vrushbabh