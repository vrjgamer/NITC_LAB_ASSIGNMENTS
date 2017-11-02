from PIL import Image as IMG
import numpy  as np

im = IMG.open("SET 1 IMAGE.tif")

# part one 
x = im.getextrema()

f = open("1A.txt", "w+")
f.write("minimum value of pixel is %d" % x[0])
f.write("maximum value of pixel is %d" % x[1])
f.close()

print "minimum value of pixel is %d" % x[0]
print "maximum value of pixel is %d" % x[1]