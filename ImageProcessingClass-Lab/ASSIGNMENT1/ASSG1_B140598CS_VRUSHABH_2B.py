from PIL import Image as IMG
import numpy as np

deltaX = 0.1
deltaY = 0.2

X = np.arange(0, 1, deltaX)
Y = np.arange(0, 1, deltaY)

func = []

x = 0
y = 0

for i in X:
    y = 0
    for j in Y:
        v = 1 + np.sin(2 * np.pi* (i + j))
        v = v/2
        func.append(v) 
        y+=1
    else:
        x+=1
        
temp = np.asarray(func) 
img = np.reshape(temp, (-1, y))

ig = IMG.fromarray(img, 'L')
print "Size of the image is: "
print ig.size

f = open("2B.txt", "w+")
f.write("Size of the image is: width= %d" % ig.size[0])
f.write(", height = %d" % ig.size[1])
f.close()
