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
Hen = defaultdict(lambda : defaultdict(lambda : "NONE"))
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
            
        
    


for i in range(1, hensosu, 1) :
    disp=""+Siten[i-1]+":"+Syuten[i-1]+"="+Senbun[i-1]
    print(disp, sep='', end='\n')
    

