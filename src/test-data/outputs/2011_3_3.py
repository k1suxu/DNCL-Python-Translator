#Template Zone
from collections import defaultdict

# DNCLの仕様に基づきfor文を閉区間にオーバーライド
def range(start :int | float, end :int | float, inc :int | float) -> list:
    list = []
    if inc > 0:
        while start <= end:
            list.append(start)
            start = start + inc
    else:
        while start >= end:
            list.append(start)
            start = start + inc
    return list

#Your Translated Code Zone



Tensu = defaultdict(lambda : 0)
sowa=0
saiko=0
saitei=100
Tensu=[0,58,86,92,30,98,61,57,19,40,29,2,86,3,30,95,98,59,97,33,81,2,50,4,19,5,49,69,46,40,56,24,64,58,29,41,65,70,77,32,14,76,44,95,2,50,42,61,99,93,29]
TNin = defaultdict(lambda : 0)
for bango in range(1, 50, 1) :
    s=Tensu[bango-1]
    sowa=s+sowa
    if s>saiko :
        saiko=s
        
    if s<saitei :
        saitei=s
        
    TNin[s-1]=TNin[s-1]+1
    

heikin=sowa//50
print(heikin, saiko, saitei, sep='', end='\n')

GNin = defaultdict(lambda : 0)
GNin[100-1]=TNin[100-1]
for ten in range(99, 0, -(1)) :
    GNin[ten-1]=GNin[ten+1-1]+TNin[ten-1]
    

Tenjun = defaultdict(lambda : 0)
Tenban = defaultdict(lambda : 0)

for bango in range(50, 1, -(1)) :
    s=Tensu[bango-1]
    Tenjun[GNin[s-1]-1]=s
    Tenban[GNin[s-1]-1]=bango
    GNin[s-1]=GNin[s-1]-1
    

juni=1
print(juni, Tenjun[1-1], Tenban[1-1], sep='', end='\n')
for i in range(2, 50, 1) :
    if Tenjun[i-1]<Tenjun[i-1-1] :
        juni=i
        
    print(juni, ":", Tenjun[i-1], ":", Tenban[i-1], sep='', end='\n')
    

