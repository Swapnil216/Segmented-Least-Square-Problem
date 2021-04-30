#!/usr/bin/env python
# coding: utf-8

# In[55]:


import re
import matplotlib.pyplot as plt
import numpy as np



with open('input.txt', 'r') as g:
    il = g.readlines()
    
z = len(il)
n = int(il[0])

xi=[]
yi=[]
for i in range(1,n+1):
    j =re.findall(r"[-+]?\d*\.\d+|[-+]?\d+", il[i])
    xi.append(int(j[0]))
    yi.append(int(j[1]))




plt.scatter(xi,yi)
plt.title('Input Points')
plt.ylabel('Y axis')
plt.xlabel('X axis')
plt.show

xi.sort()
## abline funtions plots the line 
#  input - slope , intercept , x-limit , ith plot 
#  output - plot the line by generating point by given x-limit and corresponding y values 

def abline(slope, intercept ,b, i):
    """Plot a line from slope and intercept"""
    axes = plt.gca()
    if(b[i][0]>b[i][1]):
        x_vals = np.arange(b[i][1],b[i][0],0.01)
    else:
        x_vals = np.arange(b[i][0],b[i][1],0.01)
    y_vals = intercept + slope * x_vals
    print(y_vals)
    
    
    plt.plot(x_vals, y_vals, '-',linewidth=4)
  




with open('output.txt', 'r') as f:
    lines = f.readlines()

#to store slope and intercept values 
slope = []
intercept = []


x = len(lines)
print(x)
xx=[]
yy=[]
for i in range(0,x):
    if i%2==0:
        l = re.findall(r"[-+]?\d*\.\d+|[-+]?\d+", lines[i])
        slope.append(float(l[0]))
        intercept.append(float(l[1]))
    else:
        
        m =re.findall(r'\d+', lines[i])
        xx.append((int(m[0]),int(m[1])))



b=[]
i=0
print(xx)
for items in xx:
    b.append((xi[items[0]-1],xi[items[1]-1]))
print(b)

for i in range(0,len(slope)):
    abline(slope[i], intercept[i], b ,i)
    i = i + 1

    
xx.clear()
slope.clear()
intercept.clear()


# In[ ]:




