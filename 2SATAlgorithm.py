# -*- coding: utf-8 -*-
"""
Created on Wed Jul 15 16:23:02 2020

@author: Grant
"""

import random

n = 4

x = []

conditions = [[1, 0, 1, 1], [0, 0, 2, 1], [1, 2, 3, 1], [0, 1, 3, 0]]

for a in range(n):
    number = random.randrange(0, 2)
    
    if number == 1:
        x.append(True)
    else:
        x.append(False)
        
print(x)

for i in range(0, 2 * n^2):
    satisfy = 0
    
    not_satisfy = 100
    
    for c in conditions:
        if c[0] == 1 and c[3] == 1:
            if x[c[1]] or x[c[2]]:
                satisfy += 1
            else:
                not_satisfy = 0
        elif c[0] == 1 and c[3] == 0:
            if x[c[1]] or not x[c[2]]:
                satisfy += 1
            else:
                not_satisfy = 1
        elif c[0] == 0 and c[3] == 1:
            if not x[c[1]] or x[c[2]]:
                satisfy += 1
            else:
                not_satisfy = 2
        else:
            if not x[c[1]] or not x[c[2]]:
                satisfy += 1
            else:
                not_satisfy = 3
    
    if satisfy < 4:
        number = random.randrange(0, 2)
        
        if number == 0:
            change = conditions[not_satisfy][1]
        else:
            change = conditions[not_satisfy][2]
        
        x[change] = not x[change]
    else:
        break
          
print(x)
        

