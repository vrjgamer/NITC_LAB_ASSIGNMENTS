from PIL import Image as IMG
import numpy  as np



im = IMG.open("image.tif") #load image 

img = np.array(im)


for i in range(0, img.shape[0]):
	for j in range(0, img.shape[1]):
		 img[i][j] = img[i][j] >> 4
		 img[i][j] = img[i][j] << 4
		 #print img[i][j]

outImg = IMG.fromarray(img)
outImg.convert('RGB').save('5B.jpg')
outImg.show()

























#author Vrushbabh