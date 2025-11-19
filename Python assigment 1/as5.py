k=int (input())
ok=1
i=0
while ok:
    i+=1
    if k==1:
        print(1)
        ok=0
    else:
        if i*(i-1)/2<k and i*(i+1)/2>=k:
            print(i)
            ok=0
            
