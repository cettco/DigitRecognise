'''
Created on 2013-4-24

@author: golden_zhang
'''
import math
import numpy as np
import random

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
alpha = 0.1
digit =0    #current trained digit
Error = 0
E_min = 0.1
lNum=[256,64,10]   #each layer's node number
L = 3           # layers number
m = 256
n = 64
k = 10
w0 = []
w1 = []
inLayer = []
hidenLayer = []
outLayer = []
result = []
ideality = []
def init():
    for i in range(0,n):
        for j in range(0,m):
            w0.append(random())
    for i in range(0,k):
        for j in range(0,n):
            w1.append(random())
    if digit ==0:
        ideality = v0
    if digit ==1:
        ideality = v1
    if digit ==2:
        ideality = v2
    if digit ==3:
        ideality = v3
    if digit ==4:
        ideality = v4
    if digit ==5:
        ideality = v5
    if digit ==6:
        ideality = v6
    if digit ==7:
        ideality = v7
    if digit ==8:
        ideality = v8
    if digit ==9:
        ideality = v9
        
def calculate():
    for i in range(0,n):
        sum = 0
        for j in range(0,m):
            sum = sum+w0[i*n+j]*inLayer[j]
        hidenLayer.append(sum)
    for i in range(0,k):
        sum = 0
        for j in range(0,n):
            sum = sum+w1[i*k+j]*hidenLayer[j]
        outLayer.append(sum)
def sigmoid():
    for i in range(k):
        x = outLayer[i]
        sum = 1.0/(1+math.exp(-x))
        if sum>0:
            result.append(1)
        else:
            result.append(0)
def back():
    Error = E_min + 1
    while(Error>E_min):
        Error = 0
        sum = 0
        for i in range(0,k):
            a = outLayer[i]-ideality[i]          #some errors
            sum = sum+math.pow(a,2)
        #j = L -1                                  #the below can be concrete
        #while
        for i in range(0,k):
            for j in range(0,n):
                change = alpha*ideality[i]*(1-ideality[i])*(outLayer[i]-ideality[i])*ideality[j]
                w1[i*k+j]=w1[i*k+j]+change
                
        Error = sum/2.0
        
    
def rec():
    sigmoid()
    if result==v0:
        return 0
    if result==v1:
        return 1
    if result==v2:
        return 2
    if result==v3:
        return 3
    if result==v4:
        return 4
    if result==v5:
        return 5
    if result==v6:
        return 6
    if result==v7:
        return 7
    if result==v8:
        return 8
    if result==v9:
        return 9
def begin(ilayer):
    inLayer = ilayer
