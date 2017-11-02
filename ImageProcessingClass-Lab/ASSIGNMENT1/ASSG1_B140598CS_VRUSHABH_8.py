from PIL import Image as IMG
import numpy  as np
import matplotlib.pyplot as plt

im = IMG.open("SET 1 IMAGE.tif")

extreama = im.getextrema()

mean = extreama[0] + extreama[1]
mean = mean /2

print mean

img = np.array(im)

for i in range(0, im.size[0]):
    for j in range(0, im.size[1]):
        value = img[i, j]
        if(value > mean):
            img[i,j] = 0
        else:
            img[i,j] = 255
            
outImg = IMG.fromarray(img,"L")
outImg.convert("RGB").save("8.jpg")
outImg.show()

plt.imshow(outImg, cmap="gray")
plt.show()