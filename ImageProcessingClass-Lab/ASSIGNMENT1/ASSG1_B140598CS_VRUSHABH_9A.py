#!/usr/bin/python
# -*- coding: utf-8 -*-

from PIL import Image as IMG
import numpy as np
import matplotlib.pyplot as plt

im = IMG.open('SET 1 IMAGE.tif')

def getFuncValue(sigma, intensity):
    value = np.exp(sigma) * float(intensity)
    value = 1 + value
    value = np.log(value)
    return round(value)

def getEnhancedValue(intensity, maxI):
    value = intensity/ float(maxI)
    value = value * 256
    if(value > 256):
        value = 256
    return round(value)

# sigma = 0

sigma = 0
k = 0
img = np.array(im)
iten = np.zeros(im.size[0] * im.size[1])

for i in range(0, im.size[0]):
    for j in range(0, im.size[1]):
        value = getFuncValue(sigma, img[i, j])
        img[i, j] = value
        
        
maxI = np.amax(img)
for i in range(0, im.size[0]):
    for j in range(0, im.size[1]):
        value = getEnhancedValue(img[i,j], maxI)
        img[i, j] = value
        iten[k] = value
        k += 1

plt.plot(iten)
plt.savefig('9A_graph_0.jpg')
plt.clf()
plt.cla()
plt.close()
IMG.fromarray(img, 'L').save('9A_0.jpg')

# sigma = 1

sigma = 1
k = 0
img = np.array(im)
iten = np.zeros(im.size[0] * im.size[1])

for i in range(0, im.size[0]):
    for j in range(0, im.size[1]):
        value = getFuncValue(sigma, img[i, j])
        img[i, j] = value
        
        
maxI = np.amax(img)
for i in range(0, im.size[0]):
    for j in range(0, im.size[1]):
        value = getEnhancedValue(img[i,j], maxI)
        img[i, j] = value
        iten[k] = value
        k += 1

plt.plot(iten)
plt.savefig('9A_graph_1.jpg')
plt.clf()
plt.cla()
plt.close()
IMG.fromarray(img, 'L').save('9A_1.jpg')

# sigma = 2

sigma = 2
k = 0
img = np.array(im)
iten = np.zeros(im.size[0] * im.size[1])

for i in range(0, im.size[0]):
    for j in range(0, im.size[1]):
        value = getFuncValue(sigma, img[i, j])
        img[i, j] = value
        
        
maxI = np.amax(img)
for i in range(0, im.size[0]):
    for j in range(0, im.size[1]):
        value = getEnhancedValue(img[i,j], maxI)
        img[i, j] = value
        iten[k] = value
        k += 1

plt.plot(iten)
plt.savefig('9A_graph_2.jpg')
plt.clf()
plt.cla()
plt.close()
IMG.fromarray(img, 'L').save('9A_2.jpg')

