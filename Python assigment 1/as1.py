s=0
ok=1
n=int (input())
while ok==1:
    while n>0:
        s+=n%10
        n//=10
    if s//10==0:
        ok=0
    else:
        n=s
        s=0
print(s)
