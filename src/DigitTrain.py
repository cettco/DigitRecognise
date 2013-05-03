'''
Created on May 2, 2013

@author: zhang
'''
import math
import numpy as np
import random
import pic
import Image
v0 =[0,0,0,0,0,0,0,0,0,0]
v1 =[1,0,0,0,0,0,0,0,0,0]
v2 =[0,1,0,0,0,0,0,0,0,0]
v3 =[0,0,1,0,0,0,0,0,0,0]
v4 =[0,0,0,1,0,0,0,0,0,0]
v5 =[0,0,0,0,1,0,0,0,0,0]
v6 =[0,0,0,0,0,1,0,0,0,0]
v7 =[0,0,0,0,0,0,1,0,0,0]
v8 =[0,0,0,0,0,0,0,1,0,0]
v9 =[0,0,0,0,0,0,0,0,1,0]
O =[v0,v1,v2,v3,v4,v5,v6,v7,v8,v9]
STUDY_SPEED = 0.3
LNum =[256,64,10]
D = []
W = []
wt = []
input = []

def read():
    for i in range(10):
        p = str(i)+".bmp"
        im = Image.open(p)
        out = pic.convertImg(im, 150)
        out = pic.regulateImg(out)
        data = pic.readImg(out, 32)
        input.append(data)
    D.append(input)

def init():
    num = len(LNum)
    for i in range(num-1):
        for j in range(LNum[i]):
            for k in range(LNum[i+1]):
                wt.append(random.random())
        W.append(wt)
    read()
#f, caculate the value of the node,
def f(node,layer):
    sum = 0
    for i in range(LNum[layer-1]):
        sum=sum+W[layer-1][i*LNum[layer]+node]*D[layer-1][i]
    return sum
    
def feed_forward():
    for i in range(len(1,LNum)):
        temp = []
        for j in range(LNum[i]):
            sum = f(j,i)
            temp.append(sum)
        D.append[temp]
def compute_gradient():
    for layer in range(1,len(LNum)):
        for i in range(LNum(layer)):
            for j in range(LNum(layer-1)):
                w_temp1 = W[layer][i*LNum(layer-1)+j]
                W[layer][i*LNum(layer-1)+j]

def update_weights():
    for layer in range(1,len(LNum)):
        for i in range(LNum(layer)):
            for j in range(LNum(layer-1)):
                w_temp1 = W[layer][i*LNum(layer-1)+j]
                W[layer][i*LNum(layer-1)+j]=W[layer][i*LNum(layer-1)+j]-STUDY_SPEED*
def sigmoid(x):
    return 1/(1+math.exp(-x))  

def error(x):
    sum = 0
    num = LNum[len(LNum)-1]
    for i in range(num):
        sum = sum+math.pow(math.fabs(O[x][i]-D[len(LNum)-1][i]), 2) 
    return sum
            
def train():
    
if __name__ == '__main__':
    init()