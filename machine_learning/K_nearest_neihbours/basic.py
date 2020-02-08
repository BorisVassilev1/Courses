import numpy as np
import pandas as pd
import math

K = 3

train_data = pd.read_csv('train.txt', sep = ",", header = None, names = ["A", "B", "C", "D", "E", "F", "G", "H", "I", "J"], quotechar = '\'', quoting = 1)

E_dict = {'no': 0, 'yes': 1, '?': 0.5}
D_dict = {'0-2': 1, '3-5': 2, '6-8': 3, '9-11' : 4, '12-14': 5, '15-17': 5, '18-20': 6, '21-23': 6, '24-26': 7}
C_dict = {'0-4': 1, '5-9': 2, '10-14': 3, '15-19': 4, '20-24': 5, '25-29': 6, '30-34': 7, '35-39': 8, '40-44': 9, '45-49': 10, '50-54': 11}
A_dict = {'20-29': 1, '30-39': 2, '40-49': 3, '50-59': 4, '60-69': 5, '70-79': 6}

#print(train_data)

#print(train_data.describe(include = "all"))

test_data = pd.read_csv("test.txt", sep = ",", header = None, names = ["A", "B", "C", "D", "E", "F", "G", "H", "I"], quotechar = '\'', quoting = 1)

#print(test_data)

for i, x in test_data.iterrows():
    ls = []
    for j, y in train_data.iterrows():
        distI = (not(y.get(8) == x.get(8))) + 0
        distH = (not(y.get(7) == x.get(7))) + 0
        distG = (not(y.get(6) == x.get(6))) + 0
        distF = y.get(5) - x.get(5)
        distE = E_dict[y.get(4)] - E_dict[x.get(4)]
        distD = D_dict[y.get(3)] - D_dict[x.get(3)]
        distC = C_dict[y.get(2)] - C_dict[x.get(2)]
        distB = (not(y.get(1) == x.get(1))) + 0
        distA = A_dict[y.get(0)] - A_dict[x.get(0)]
        dist = math.sqrt(distI * distI + distH * distH + distG * distG + distF * distF + distE * distE + distD * distD + distC * distC + distB * distB + distA * distA)
        #print(dist)
        ls.append((dist, y.get(9)))
    ls = sorted(ls, key = lambda x: x[0])
    ans1 = 0
    ans2 = 0
    for x in ls[:K]:
        if x[1] == 'recurrence-events':
            ans1+=1
        elif x[1] == 'no-recurrence-events':
            ans2+=1
    print('recurrence-events' if ans1 > ans2 else 'no-recurrence-events')