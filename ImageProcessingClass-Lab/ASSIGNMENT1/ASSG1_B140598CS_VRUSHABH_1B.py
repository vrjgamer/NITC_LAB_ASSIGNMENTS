from PIL import Image as IMG
import numpy  as np
im = IMG.open("SET 1 IMAGE.tif")
#intensity 2 ^ x bits here 4
newImg=im.quantize(colors=16,method=None,kmeans=1,palette=None)
newImg.save("1B.tif")
newImg.show()