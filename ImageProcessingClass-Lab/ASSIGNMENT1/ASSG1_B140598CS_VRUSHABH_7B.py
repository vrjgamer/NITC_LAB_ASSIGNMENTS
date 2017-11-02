from PIL import Image as IMG
import numpy  as np

im = IMG.open("SET 1 IMAGE.tif")

max_intensity = 255 # im.getextrema()[1]

img = np.array(im)
arr = np.zeros(im.size)

interval = max_intensity/8

for i in range(0, im.size[0]):
    for j in range(0, im.size[1]):
        value = img[i, j]
        if(value>=0 and value<interval):
            value = 0
        if(value>=interval and value < 2*interval):
            value = interval
        if(value>=2*interval and value < 3*interval):
            value =2*interval
        if(value>=3*interval and value < 4*interval):
            value =3*interval
        if(value>=4*interval and value < 5*interval):
            value =4*interval
        if(value>=5*interval and value < 6*interval):
            value =5*interval
        if(value>=6*interval and value < 7*interval):
            value =6*interval
        if(value>= 7*interval and value < max_intensity):
            value = 7*interval
        if(value > max_intensity):
            value = max_intensity
        arr[i, j] = value

outImg = IMG.fromarray(arr)
outImg.convert('RGB').save('7B.jpg')
outImg.show()

f = open("7B.txt", "w+")
f.write("The quality of image is much sharper in part B than part A, as the level of quantization is more in part B\n")

