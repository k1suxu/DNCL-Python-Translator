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



tate=9
yoko=11
Masu = defaultdict(lambda : defaultdict(lambda : 0))
Masu=[
[1,1,1,1,1,1,1,1,1],
[1,0,0,0,1,0,0,0,1],
[1,1,1,0,0,0,1,0,1],
[9,0,0,0,1,0,1,0,1],
[1,1,1,0,1,0,1,0,1],
[1,0,1,1,1,0,1,1,1],
[1,0,0,0,1,0,1,0,1],
[1,1,1,0,0,0,1,0,9],
[1,0,0,0,1,1,1,0,1],
[1,0,1,0,0,0,0,0,1],
[1,1,1,1,1,1,1,1,1]
]

for y in range(2, tate-1, 1) :
    for x in range(2, yoko-1, 1) :
        i=x
        j=y
        while Masu[i-1][j-1] == 0 and Masu[i+1-1][j-1]+Masu[i-1-1][j-1]+Masu[i-1][j+1-1]+Masu[i-1][j-1-1] == 3 :
            Masu[i-1][j-1]=1
            di=Masu[i-1-1][j-1]-Masu[i+1-1][j-1]
            dj=Masu[i-1][j-1-1]-Masu[i-1][j+1-1]
            i=i+di
            j=j+dj
            
        
    
for y in range(1, tate, 1) :
    for x in range(1, yoko, 1) :
        if Masu[x-1][y-1] == 1 :
            print("■", sep='', end='\n')
        else :
            print("□", sep='', end='\n')
            
        
    print("\n", sep='', end='\n')
    

