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



HKosu = defaultdict(lambda : 0)
HOmosa = defaultdict(lambda : 0)
SOmosa = defaultdict(lambda : 0)
SOmosa=[2,8,1,1,6,6,1,2]
syohinsu=8
hakosu=0
for i in range(1, syohinsu, 1) :
    j=hakosu+1
    k=1
    while k <= hakosu :
        if (HOmosa[k-1]+SOmosa[i-1] <= 9 and HKosu[k-1]<4) and HOmosa[j-1]<HOmosa[k-1] :
            j=k
            
        k=k+1
        
    print(i, "番の商品を", j, "番の箱に入れる", sep='', end='\n')
    HOmosa[j-1]=HOmosa[j-1]+SOmosa[i-1]
    HKosu[j-1]=HKosu[j-1]+1
    if j>hakosu :
        hakosu=j
    
print("必要な箱の数は", hakosu, "である", sep='', end='\n')

