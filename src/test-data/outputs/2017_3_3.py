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



tyotensu=8
Hen = defaultdict(lambda : defaultdict(lambda : ""))
Hen=[
["-","A","B","-","A","-","A","B"],
["-","-","-","C","A","-","A","C"],
["-","-","-","E","-","E","E","B"],
["-","-","-","-","-","E","E","C"],
["-","-","-","-","-","D","A","D"],
["-","-","-","-","-","-","E","D"],
["-","-","-","-","-","-","-","F"]
]
Siten = defaultdict(lambda : 0)
Syuten = defaultdict(lambda : 0)
Senbun = defaultdict(lambda : 0)
hensosu=0

for i in range(1, tyotensu-1, 1) :
    for j in range(i+1, tyotensu, 1) :
        if Hen[i-1][j-1] != "-" :
            hensosu=hensosu+1
            Siten[hensosu-1]=i
            Syuten[hensosu-1]=j
            Senbun[hensosu-1]=Hen[i-1][j-1]
            
        
    
kotae=0
for x in range(1, hensosu-2, 1) :
    y=x+1
    while Siten[x-1] == Siten[y-1] :
        if Senbun[x-1] != Senbun[y-1] and Hen[Syuten[x-1]-1][Syuten[y-1]-1] != "-" :
            kotae=kotae+1
            
        y=y+1
        
    
print("三角形の個数は", kotae, "個である", sep='', end='\n')

