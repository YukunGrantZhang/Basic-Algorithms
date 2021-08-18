# -*- coding: utf-8 -*-
"""
Created on Wed Jul 15 09:01:37 2020

@author: Grant
"""

items = [[2, 1], [4, 3], [3, 3]]
w = 5

for i in range(0, len(items)):
    ratio = items[i][0]/items[i][1]
    
    items[i].append(ratio)

items.sort(key=lambda x: x[2], reverse=True)

print(items)

output_items = []
weights_sum = 0
for i in range(0, len(items)):
    output_items.append([items[i][0], items[i][1]])
    weights_sum += items[i][1]
    
    if i < len(items) - 1:
        if weights_sum + items[i + 1][1] > w:
            break

for i in range(0, len(items)):
    if items[i][1] > weights_sum and items[i][1] <= w:
        output_items.clear()
        output_items.append([items[i][0], items[i][1]])
        weights_sum = items[i][1]

print(output_items)