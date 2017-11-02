from PIL import Image as IMG
import numpy  as np


im = IMG.open('image.tif') # load the image
 
x = im.getextrema() # find extreme values of the intensity

print "minimum value of pixel is %d" % x[0] #output minimum value

print "maximum value of pixel is %d" % x[1] #output maximum value




#author Vrushbabh