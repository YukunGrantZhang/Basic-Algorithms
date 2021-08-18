# -*- coding: utf-8 -*-
"""
Created on Thu Jul 16 10:10:03 2020

@author: Grant
"""

man = [[0, 1, 2], [0, 1, 2], [0, 1, 2]]

woman = [[0, 1, 2], [1, 2, 0], [2, 0, 1]]

man_engagements = [100, 100, 100]

man_rejection_list = [[], [], []]

woman_engagements = [100, 100, 100]

def galeshapeley(n):
    global man
    global woman
    global man_engagements
    global man_rejection_list
    global woman_engagements
    
    while 100 in man_engagements or 100 in woman_engagements:
        for m in range(0, n):
            if man_engagements[m] == 100:
                choose_man = m
        
        for c in range(0, n):            
            if man[choose_man][c] not in man_rejection_list[choose_man]:
                if woman_engagements[man[choose_man][c]] == 100:
                    choose_woman = man[choose_man][c]
                    break
                else:
                    if woman[man[choose_man][c]].index(choose_man) < woman[man[choose_man][c]].index(woman_engagements[man[choose_man][c]]):
                        choose_woman = man[choose_man][c]
                        man_engagements[woman_engagements[choose_woman]] = 100
                        man_rejection_list[woman_engagements[choose_woman]].append(choose_woman)
                        break
                    else:
                        continue
        
        man_engagements[choose_man] = choose_woman
        woman_engagements[choose_woman] = choose_man

galeshapeley(3)

print(man_engagements)
print(woman_engagements)