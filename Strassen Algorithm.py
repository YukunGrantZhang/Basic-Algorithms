# -*- coding: utf-8 -*-
"""
Created on Fri Jun 12 11:01:15 2020

@author: Grant
"""

import numpy as np
import math

my_matrix1 = np.array([[1, 2, 3, 4], [5, 6, 7, 8], [9, 10, 11, 12], [13, 14, 15, 16]])
my_matrix2 = np.array([[1, 2, 3, 4], [5, 6, 7, 8], [9, 10, 11, 12], [13, 14, 15, 16]])

m1 = np.array([[1, 2], [3, 4]])
m2 = np.array([[5, 6], [7, 8]])

master_matrix = []

def strassen_operation(matrix_a, matrix_b):
    p1 = matrix_a[0][0] * (matrix_b[0][1] - matrix_b[1][1])
    p2 = (matrix_a[0][0] + matrix_a[0][1]) * matrix_b[1][1]
    p3 = (matrix_a[1][0] + matrix_a[1][1]) * matrix_b[0][0]
    p4 = matrix_a[1][1] * (matrix_b[1][0] - matrix_b[0][0])
    p5 = (matrix_a[0][0] + matrix_a[1][1]) * (matrix_b[0][0] + matrix_b[1][1])
    p6 = (matrix_a[0][1] - matrix_a[1][1]) * (matrix_b[1][0] + matrix_b[1][1])
    p7 = (matrix_a[0][0] - matrix_a[1][0]) * (matrix_b[0][0] + matrix_b[0][1])
    
    c11 = p5 + p4 -p2 + p6
    c12 = p1 + p2
    c21 = p3 + p4
    c22 = p1 + p5 - p3 - p7
    
    C = np.vstack([np.hstack([c11, c12]), np.hstack([c21, c22])])
    
    return C

def partition(my_matrix1, my_matrix2):
    global master_matrix
    
    upper_half1 = np.hsplit(np.vsplit(my_matrix1, 2)[0], 2)
    lower_half1 = np.hsplit(np.vsplit(my_matrix1, 2)[1], 2)
    
    upper_half2 = np.hsplit(np.vsplit(my_matrix2, 2)[0], 2)
    lower_half2 = np.hsplit(np.vsplit(my_matrix2, 2)[1], 2)

    upper_left1 = upper_half1[0]
    upper_right1 = upper_half1[1]
    lower_left1 = lower_half1[0]
    lower_right1 = lower_half1[1]
    
    upper_left2 = upper_half2[0]
    upper_right2 = upper_half2[1]
    lower_left2 = lower_half2[0]
    lower_right2 = lower_half2[1]
    
    if len(my_matrix1) > 2:
        partition(upper_left1, upper_left2)
        partition(upper_right1, upper_right2)
        partition(lower_left1, lower_left2)
        partition(lower_right1, lower_right2)
    else:
        first_matrix = np.vstack([np.hstack([upper_left1, upper_right1]), np.hstack([lower_left1, lower_right1])])
        second_matrix = np.vstack([np.hstack([upper_left2, upper_right2]), np.hstack([lower_left2, lower_right2])])
        
        result = strassen_operation(first_matrix, second_matrix)
        
        if len(result) > 1:
            master_matrix.append(result)
        
        return result
        
def multiply(my_matrix1, my_matrix2):
    global master_matrix
    
    answer = []
    
    partition(my_matrix1, my_matrix2)
    
    length = int(math.sqrt(len(master_matrix)))
    
    x = 0
    
    for a in range(length):
        temp_elements = []
        
        for b in range(length):
            temp_elements.append(master_matrix[x])
            x += 1
        
        answer.append(np.hstack(temp_elements))
    
    return np.vstack(answer)
    
print(multiply(my_matrix1, my_matrix2))
