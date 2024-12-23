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



Suji = defaultdict(lambda : "")
KuraiMoji = defaultdict(lambda : "")
OkinaKuraiMoji = defaultdict(lambda : "")
Suji[1-1]=""
Suji[2-1]="二"
Suji[3-1]="三"
Suji[4-1]="四"
Suji[5-1]="五"
Suji[6-1]="六"
Suji[7-1]="七"
Suji[8-1]="八"
Suji[9-1]="九"
KuraiMoji[4-1]="千"
KuraiMoji[3-1]="百"
KuraiMoji[2-1]="十"
KuraiMoji[1-1]=""
OkinaKuraiMoji[3-1]="億"
OkinaKuraiMoji[2-1]="万"
OkinaKuraiMoji[1-1]=""

okinaKurai=100000000
x=123456789
d=1
for kugiri in range(3, 1, -(1)) :
    n=x//okinaKurai
    if d != 0 :
        kurai=1000
        for keta in range(4, 1, -(1)) :
            d=n//kurai
            if d != 0 :
                if d == 1 and keta == 1 :
                    print("一", sep='', end='\n')
                else :
                    print(Suji[d-1], sep='', end='\n')
                    print(KuraiMoji[keta-1], sep='', end='\n')
                    
                
            n=n%kurai
            kurai=kurai//10
            
        print(OkinaKuraiMoji[kugiri-1], sep='', end='\n')
        
    x=x%okinaKurai
    okinaKurai=okinaKurai//10000
    

