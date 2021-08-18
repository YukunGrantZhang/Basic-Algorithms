# -*- coding: utf-8 -*-
"""
Created on Fri Jul 10 10:00:23 2020

@author: Grant
"""

String1 = "AGGGCT"
String2 = "AGG-CA"

X = list(String1)
Y = list(String2)

X_align = X
Y_align = Y

match = 1
mismatch = -1
delete = -1

m = len(X) + 1
n = len(Y) + 1

A = []

for a in range(0, m):
    A.append([])

for r in range(0, m):
    A[r].append(r * delete)

for s in range(1, n):
    A[0].append(s * delete)

for i in range(1, m):
    for j in range(1, n):
        m_1 = X[i - 1]
        m_2 = Y[j - 1]
        
        if m_1 == m_2:
            match_penalty = match
        else:
            match_penalty = mismatch
        
        case_1 = A[i - 1][j - 1] + match_penalty
        case_2 = A[i - 1][j] + delete
        case_3 = A[i][j - 1] + delete
        
        max_value = max(case_1, case_2, case_3)
        
        A[i].append(max_value)

print(A)

i = m - 1
j = n - 1

while i > 0 and j > 0:
    m_1 = X[i - 1]
    m_2 = Y[j - 1]
        
    if m_1 == m_2:
        match_penalty = match
    else:
        match_penalty = mismatch
        
    case_1 = A[i - 1][j - 1] + match_penalty
    case_2 = A[i - 1][j] + delete
    case_3 = A[i][j - 1] + delete
    
    max_value = max(case_1, case_2, case_3)
    
    if max_value == case_1:
        if match_penalty == match:
            X_align[i - 1] = m_1
            Y_align[j - 1] = m_2
        else:
            X_align[i - 1] = " "
            Y_align[j - 1] = " "
            
        i -= 1
        j -= 1
    elif max_value == case_2:
        X_align[i - 1] = " "
        i -= 1
    else:
        Y_align[j - 1] = " "
        j -= 1

if i == 0:
    while j > 0:
        Y_align[j - 1] = " "
        j -= 1

if j == 0:
    while i > 0:
        X_align[i - 1] = " "
        i -= 1

print(X_align)
print(Y_align)