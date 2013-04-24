'''
Created on 2013-4-24

@author: golden_zhang
'''
from train import *
from pic import *
def reccognition(im):
    data = readImg(im)
    begin(data)
    a = rec()
    print a