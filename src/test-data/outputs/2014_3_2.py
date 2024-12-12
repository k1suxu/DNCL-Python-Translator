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



Gakuhu = defaultdict(lambda : "NONE")
Patan = defaultdict(lambda : "NONE")
Kakegoe = defaultdict(lambda : "NONE")
Gakuhu=["ダ","カ","ン","コ","ド","終"]
Patan=["カ","ン","コ","声"]
yameru=0
i=1
while yameru == 0 :
    itti=0
    j=1
    while Patan[j-1] != "声" :
        if Gakuhu[i+j-1-1] == Patan[j-1] :
            itti=itti+1
            
        j=j+1
        
    if Gakuhu[i+j-1-1] == "終" :
        yameru=1
    if itti == j-1 :
        Kakegoe[i+j-1-1]="▽"
        
    i=i+1
    
print(Kakegoe, sep='', end='\n')

