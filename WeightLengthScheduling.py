# -*- coding: utf-8 -*-
"""
Created on Wed Jul  1 11:22:12 2020

@author: Grant
"""

task_weights = [3, 5, 1, 6, 8, 11, 15, 6, 8, 9, 2, 11, 6, 8, 11, 16, 11, 3, 8]

task_lengths = [11, 28, 31, 25, 15, 21, 26, 19, 51, 28, 33, 31, 26, 38, 19, 29, 32, 53, 12]

length = len(task_weights)

tasks = []
for a in range(length):
    temp = []
    temp.append(a + 1)
    temp.append(task_weights[a])
    temp.append(task_lengths[a])
    tasks.append(temp)

tasks_ratios = []
for b in range(length):
    temp = []
    temp.append(b + 1)
    temp.append(task_weights[b]/task_lengths[b])
    tasks_ratios.append(temp)

tasks_ratios.sort(key=lambda x: x[1], reverse=True)

for c in range(length):
    print("Tasks", tasks_ratios[c][0])
    
    