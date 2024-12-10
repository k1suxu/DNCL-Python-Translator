#coding: shift_jis

#Template Zone
from collections import defaultdict

def range(start :float, end :float, inc :float) -> list:
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



Namae = defaultdict(lambda : "NONE")
Tokuten = defaultdict(lambda : 0)
Namae[1-1]="はるこ"
Tokuten[1-1]=73
Namae[2-1]="なつお"
Tokuten[2-1]=77
Namae[3-1]="あきよ"
Tokuten[3-1]=81
Namae[4-1]="ふゆき"
Tokuten[4-1]=68

for j in range(4-1, 1, -(1)) :
    for i in range(1, j, 1) :
        if Tokuten[i-1]<Tokuten[i+1-1] :
            n=Namae[i-1]
            Namae[i-1]=Namae[i+1-1]
            Namae[i+1-1]=n
            t=Tokuten[i-1]
            Tokuten[i-1]=Tokuten[i+1-1]
            Tokuten[i+1-1]=t
            
        
    


for i in range(1, 4, 1) :
    txt=Namae[i-1]+":"+Tokuten[i-1]
    print(txt, sep='', end='\n')
    

