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

# to find Inverse Fourier Transform
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
	N = int(input("Enter a N: ")) # get the value of N
	f = np.zeros(N) # create an array of N integers
	 
	for i in range(0, N):
			f[i] = int(input("Enter 'f' sequence entry: ")) # get values of the integers for the array

	#finding fourierTransform
	F = fourierTransform(f, N)

	print "Fourier output: ",F #output of the Fourier Transform

	
	F[0] = 0 #changing F[0] to 0
	result = np.zeros(N) #result array
		
	result = inverseFourierTransform(F, N) #finding inverse Fourier Transform

	print "Inverse Fourier output: ",result # final output

	return

main() # call main function


#author Vrushbabh