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



Yakusu = defaultdict(lambda : 0)
for i in range(2, 100, 1) :
    Yakusu[i-1]=0
    

for i in range(2, 100, 1) :
    if Yakusu[i-1] == 0 :
        j=i
        while j <= 100 :
            Yakusu[j-1]=i
            j=j+i
            
        
    

for i in range(2, 100, 1) :
    if Yakusu[i-1] == i :
        print(i, sep='', end='\n')
        
    

