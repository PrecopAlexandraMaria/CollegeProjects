for i in range(0, 9):
    if((i*i)%10==i):
        for n in range (0,100,10):
            n+=i
            print(n)
            n-=i
#toate cifrele care au unitatea patratului perfect egala cu ele, vor avea aceeasi
# proprietate pentru toate numerele pentru care sunt unitati