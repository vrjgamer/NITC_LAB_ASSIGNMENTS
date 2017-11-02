from PIL import Image as IMG
import numpy  as np

im = IMG.open("SET 1 IMAGE.tif")

max_intensity = 255 # im.getextrema()[1]

img = np.array(im)
arr = np.zeros(im.size)

interval = max_intensity/4

for i in range(0, im.size[0]):
    for j in range(0, im.size[1]):
        value = img[i, j]
        if(value>=0 and value<interval):
            value = 0
        if(value>=interval and value < 2*interval):
            value = interval
        if(value>=2*interval and value < 3*interval):
            value =2*interval
        if(value>= 3*interval and value < max_intensity):
            value = 3*interval
        if(value > max_intensity):
            value = max_intensity
        arr[i, j] = value

outImg = IMG.fromarray(arr)
outImg.convert('RGB').save('7A.jpg')
outImg.show()