from PIL import Image as IMG
import numpy  as np
import math

im = IMG.open('images.jpeg')

quantize = np.array([[16,11,10,16,24,40,51,61],[12,12,14,19,26,58,60,55],[14,13,16,24,40,57,69,56],[14,17,22,29,51,87,80,62],[18,22,37,56,68,109,103,77],[24,35,55,64,81,104,113,92],[49,64,78,87,103,121,120,101],[72,92,95,98,112,100,103,99]])

threshold = 1

def getSubMatrix(buf):
	for i in xrange(0, 16, 1):
		if(i > buf.shape[0]):
			break
		for j in xrange(0, 16, 1):
			if(j > buf.shape[1]):
				break
			buf[i, j] = buf[i, j] - 127
	return buf

def alphafunc(n):
	if n == 0 :
		return 0.2500
	else:
		return 0.3535
	
def DCTValue(buf, u , v):
	sum = 0
	alphau = alphafunc(u)
	alphav = alphafunc(v)
	for x in xrange(0, 16, 1):
		for y in xrange(0, 16, 1):
			sum = sum + (buf[x,y] * (math.cos((math.pi*u/8)*(x + 0.5))) * (math.cos((math.pi*v/8)*(y + 0.5))))
	return alphau * alphav * sum
	
def getQuantizedValue(r, i, j):
	x = i%8
	y = j%8
	return round(r/quantize[x,y] * threshold)

def getDCTMatrix(buf):
	for i in xrange(0, 16, 1):
		if(i > buf.shape[0]):
			break
		for j in xrange(0, 16, 1):
			if(j > buf.shape[1]):
				break
 			buf[i, j] = getQuantizedValue(DCTValue(buf, i, j), i, j)
	return buf

def zigZag(inputArr):
	result = []
	rows = inputArr.shape[0]
	cols = inputArr.shape[1]
	for sum in range(0, (rows + cols - 1)):
		if(sum%2 == 0):
			i = min(sum, rows - 1)
			j = sum - i
			while((i >= 0) and (j < cols)):
				result.append(inputArr[i, j])
				i -= 1
				j += 1
		else:
			j = min(sum, cols - 1)
			i = sum - j
			while((j >= 0) and (i < rows)):
				result.append(inputArr[i, j])
				i += 1
				j -= 1
	return np.array(result)


im = im.split()[0]
image = np.array(im)
arr = []

sx = 0
sy = 0
ex = 16
ey = 16

while ex < im.size[0]:
	while ey < im.size[1]:
		buffer = np.zeros(shape=(16, 16))
		buffer = buffer.astype(np.int64)
		for i in xrange(0, 16, 1):
			if (sx + i) >= im.size[0]:
				break
			for j in xrange(0, 16, 1):
				if (sy + j) >= im.size[1]:
					break
				buffer[i, j] = image[sx+i, sy+j]
		sy = ey
		ey = ey + 16
		if ey >= im.size[1]:
			ey = im.size[1]
		print "initial", buffer
		buffer = getSubMatrix(buffer)
		print "after shift", buffer
		buffer = getDCTMatrix(buffer)
		print "after DCT", buffer
		file = "buffers/buffer_" + str(sx) + "_" + str(ex) +"_"+ str(sy)+"_"+ str(ey)+".jpeg"
		img = IMG.fromarray(buffer, "L")
		img.convert('L').save(file)
		d = zigZag(buffer)
		print d
		arr.append(np.array(d))
	else:
		sx = ex
		ex = ex + 16
		if ex >= im.size[0]:
			ex = im.size[0]
		sy = 0
		ey = 16
else:
	print "end"
	
print arr