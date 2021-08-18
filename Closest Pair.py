# -*- coding: utf-8 -*-
"""
Created on Sat Jun 13 10:01:19 2020

@author: Grant
"""

import math

points = [[6, 9],[3, 5],[1, 8],[5, 6],[11, 15],[2, 9],[7, 8]]

delta = 100
closest_pair = []

def Distance(Pair_Points):
    return math.sqrt((Pair_Points[0][0]-Pair_Points[1][0])**2 + (Pair_Points[0][1]-Pair_Points[1][1])**2)

def ClosestSplitPair(Px, Py, minimum_distance):
    global delta
    global closest_pair
    
    Px_length = len(Px)
    x_bar = Px[Px_length//2 - 1][0]
    
    x_bar_min = x_bar - minimum_distance
    x_bar_max = x_bar + minimum_distance
    
    Sy = []
    
    Py_length = len(Py)
    
    for a in range(Py_length):
        if Py[a][0] > x_bar_min and Py[a][0] < x_bar_max:
            Sy.append(Py[a])
    
    Sy_length = len(Sy)
    inner_range = min(7, Sy_length)
    
    for b in range(Sy_length):
        for c in range(inner_range):
            points = []
            
            if b + c > Sy_length - 1 or b == b + c:
                continue
            
            Point_i = Sy[b]
            Point_j = Sy[b + c]
            
            points.append(Point_i)
            points.append(Point_j)
            
            if Distance(points) < delta:
                delta = Distance(points)
                closest_pair = points
                
def ClosestPair(Px, Py):
    global delta
    global closest_pair
    
    Px_length = len(Px)
    middle_index_x = Px_length//2
    
    Qx = Px[:middle_index_x]
    Rx = Px[middle_index_x:]
    
    Py_length = len(Py)
    middle_index_y = Py_length//2
    
    Qy = Py[:middle_index_y]
    Ry = Py[middle_index_y:] 
    
    if len(Qx) > 2:
        ClosestPair(Qx, Qy)
        ClosestPair(Rx, Ry)
        ClosestSplitPair(Px, Py, delta)
    else:
        if len(Qx) == 2:
            d1 = Distance(Qx)
            d2 = Distance(Qy)
            
            if d1 < delta:
                delta = d1
                closest_pair = Qx
            
            if d2 < delta:
                delta = d2
                closest_pair = Qy
        
        if len(Rx) == 2:
            d1 = Distance(Rx)
            d2 = Distance(Ry)
            
            if d1 < delta:
                delta = d1
                closest_pair = Rx
            
            if d2 < delta:
                delta = d2
                closest_pair = Ry

def Minimum_Distance(input_points):
    points_x = sorted(input_points, key=lambda x: x[0])
    points_y = sorted(input_points, key=lambda x: x[1])
    
    ClosestPair(points_x, points_y)

Minimum_Distance(points)
print(delta)
print(closest_pair)