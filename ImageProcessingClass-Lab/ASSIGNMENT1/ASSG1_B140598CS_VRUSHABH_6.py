from PIL import Image as IMG
import numpy  as np

im = IMG.open("SET 1 IMAGE.tif")

max_intensity = 255 # im.getextrema()[1]

img = np.array(im)
arr = np.zeros(im.size)

addValue = max_intensity/4

for i in range(0, im.size[0]):
    for j in range(0, im.size[1]):
        x = img[i, j] + addValue
        if (x > max_intensity):
            x = max_intensity
        arr[i, j] = x
        
outImg = IMG.fromarray(arr)
outImg.convert('RGB').save('6.jpg')
outImg.show()