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



i=0

x=713
Kekka1 = defaultdict(lambda : 0)
while x>0 :
    Kekka1[i-1]=x%2
    x=x//2
    i=i+1
    
for j in range(9, 0, -(1)) :
    if Kekka1[j-1] == 1 :
        print(j, "番の分銅を右の皿にのせる。", sep='', end='\n')
        
    

