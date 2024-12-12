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



Sara = defaultdict(lambda : "NONE")
Sara[1-1]="右"
Sara[2-1]="左"
i=0
Kekka2 = defaultdict(lambda : 0)
x=97
while x>0 :
    amari=x%3
    x=x//3
    Kekka2[i-1]=amari
    if amari == 2 :
        x=x+1
    i=i+1
    
for j in range(6, 0, -(1)) :
    if Kekka2[j-1] != 0 :
        print(j, "番の分銅を", Sara[Kekka2[j-1]-1], "の皿にのせる。", sep='', end='\n')
        
    

