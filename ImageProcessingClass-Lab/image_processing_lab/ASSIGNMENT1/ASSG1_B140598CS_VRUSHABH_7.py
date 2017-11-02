from PIL import Image as IMG
import numpy as np
import matplotlib.pyplot as plt

def getPixelValue(i, j):
    value = np.sin((np.sqrt((i**2+j**2))))
    value = np.abs(value)
    return value;

c = np.zeros((32, 32))

for i in range(0, 32):
    for j in range(0, 32):
        c[i, j] = getPixelValue(i, j)

img = IMG.fromarray(c, "L")
img.convert('RGB').save('7.jpg')
img.show()

plt.imshow(c, cmap="gray")
plt.show()











#author Vrushbabh