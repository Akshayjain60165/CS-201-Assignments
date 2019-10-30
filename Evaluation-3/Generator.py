# -*- coding: utf-8 -*-
"""
Created on Wed Oct 30 19:50:56 2019

@author: roronoa_
"""

"""
    This is a generator function that generates the correct input sequence for this evaluation.
"""
import random

n=random.randint(10,50000)

file=open("t1.txt","w")

i=0

file.write(str(n)+"\n")

s=[]

while i<n:
    s.append(str(random.randint(0,1)))
    i=i+1
m=random.randint(1,int(100000000/n))

s1=''.join(map(str,s))

i=0

file.write(s1+"\n")
file.write(str(m)+"\n")

while i<m:
    a1=random.randint(1,n)
    b1=random.randint(a1+1,n+1)
    a2=random.randint(1,n)
    b2=random.randint(a2+1,n+1)
    if b1-a1<b2-a2 :
        b1+=(b2-a2-(b1-a1))
        if b1>n :
            a1-=(b1-n)
            b1=n
    if b1-a1>b2-a2 :
        b2+=(b1-a1-(b2-a2))
        if b2>n :
            a2-=(b2-n)
            b2=n
    #print(str(a1)+" " +str(b1)+" "+str(a2)+" "+str(b2))
    file.write(str(a1)+" " +str(b1)+" "+str(a2)+" "+str(b2)+"\n")
    i=i+1
