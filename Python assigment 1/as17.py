n=int(input())
ok=0
m=0
for m in range(n):
    s=0
    nr=m
    while nr>0:
        s+=nr%10
        nr//=10
    if (m+s==n):
        ok=1
        break
if (ok==1):
    print(n," este special")
else:
    print(n," nu este special")
#verificam toate numerele pana la n pana gasim un m care respecta cerinta