
from PIL import Image as IMG
import numpy as np
import matplotlib.pyplot as plt

def getPixelValue(i, j):
    value = np.sin((np.sqrt((i**2+j**2))))
    value = np.abs(value)
    if(value>=0 and value<0.25):
        value = 0
    if(value>=0.25 and value < 0.5):
        value = 0.25
    if(value>=0.5 and value < 0.75):
        value = 0.75
    if(value>= 0.75 and value < 1):
        value = 0.75
    if(value > 1):
        value = 1
    return value;

c = np.zeros((32, 32))

for i in range(0, 32):
    for j in range(0, 32):
        c[i, j] = getPixelValue(i, j)

img = IMG.fromarray(c, "L")
img.convert('RGB').save('5.jpg')
img.show()

plt.imshow(c, cmap="gray")
plt.show()