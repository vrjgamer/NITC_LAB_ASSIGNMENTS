from PIL import Image as IMG
import numpy as np
import matplotlib.pyplot as plt

deltaX = 0.01
deltaY = 0.01

X = np.arange(0, 1, deltaX)
Y = np.arange(0, 1, deltaY)

img = np.zeros((100, 100))

x = 0
y = 0

for i in X:
    for j in Y:
        v = 1 + np.sin(2 * np.pi* (i + j))
        v = v/2
        img[x, y] = v
        y+=1
    else:
        x+=1
        y = 0
        
i = IMG.fromarray(img, 'L')
i.save("2A.jpg")

i = plt.imshow(img, cmap="gray")
plt.show()