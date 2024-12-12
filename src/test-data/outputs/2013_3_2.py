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



Rieki = defaultdict(lambda : 0)
Rieki=[1,-3,2,10,-4,12,8,-4]
saidaiRieki=0
kaisi=0
syuryo=0
for i in range(1, 8, 1) :
    soRieki=0
    for j in range(i, 8, 1) :
        soRieki=soRieki+Rieki[j-1]
        if soRieki>saidaiRieki :
            saidaiRieki=soRieki
            kaisi=i
            syuryo=j
            
        
    
print("開始時間帯は", kaisi, ", し,", sep='', end='\n')
print("終了時間帯は", syuryo, ", する。", sep='', end='\n')
print("総利益の最大値は", saidaiRieki, "千円である。", sep='', end='\n')

