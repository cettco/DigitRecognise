'''
Created on 2013-4-24

@author: golden_zhang
'''
from pic import *
import Image
if __name__ == '__main__':
    im = Image.open("0.bmp")
    out = regulateImg(im)
    out = convertImg(out,150)
    out.save("a.bmp")
    sourcedata = []
    sourcedata = readImg(out,32)
    print sourcedata