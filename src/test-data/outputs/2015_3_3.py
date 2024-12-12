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



M = defaultdict(lambda : defaultdict(lambda : 0))
M[1-1]=[20,5,15,20]
M[2-1]=[10,30,10,10]
M[3-1]=[10,30,5,50]
M[4-1]=[10,10,15,20]
M[5-1]=[40,10,20,30]
x=1
y=1
tokuten=M[1-1][1-1]
xMasu=5
yMasu=4

T = defaultdict(lambda : defaultdict(lambda : 0))

for y in range(1, yMasu, 1) :
    for x in range(1, xMasu, 1) :
        if M[x-1-1][y-1] == M[x-1][y-1] :
            xTokuten=T[x-1-1][y-1]+M[x-1][y-1]*2
        else :
            xTokuten=T[x-1-1][y-1]+M[x-1][y-1]
            
        if M[x-1][y-1-1] == M[x-1][y-1] :
            yTokuten=T[x-1][y-1-1]+M[x-1][y-1]*2
        else :
            yTokuten=T[x-1][y-1-1]+M[x-1][y-1]
            
        if xTokuten >= yTokuten :
            T[x-1][y-1]=xTokuten
        else :
            T[x-1][y-1]=yTokuten
            
        
    
print("最大得点の最大値は", T[xMasu-1][yMasu-1], "点である。", sep='', end='\n')

