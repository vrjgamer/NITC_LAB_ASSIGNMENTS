#!/usr/bin/python
# -*- coding: utf-8 -*-

from PIL import Image as IMG
import numpy as np


def getPixelValue(i, j):
    value = 0
    c1 = 0
    c2 = 255
    if i / 8 % 2 == 0:
        c1 = 0
        c2 = 255
    else:
        c1 = 255
        c2 = 0

    if j / 8 % 2 == 0:
        value = c2
    else:
        value = c1

    return value


chess = np.zeros((64, 64))

for i in range(0, 64):
    for j in range(0, 64):
        chess[i, j] = getPixelValue(i, j)

img = IMG.fromarray(chess)
img.convert('RGB').save('3.jpg')
img.show()

