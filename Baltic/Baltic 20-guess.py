l, r = 1, int(input())
while 1:
    m = (l + r) // 2
    print(f'? {m}')
    a = int(input())
    if a < 0:
        l = m + 1
    if a > 0:
        r = m - 1
    if a == 0:
        print(f'= {m}')
        break
