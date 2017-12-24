import time
import sys
import pyocr
import pyocr.builders
from PIL import Image

for i in range(0, 4):
    for j in range(0, 4):
        box = (0 + 100 * j, 0 + 100 * i, 100 + 100 * j, 100 + 100 * i)
        im = Image.open("./ring.png")
        im = im.crop(box)
        name = str(i * 4 + j + 1) + ".png"
        im.save(name)
