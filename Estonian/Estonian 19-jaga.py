fin = open('jagasis.txt', 'r')
fout = open('jagaval.txt', 'w')

n = int(fin.readline())
a = []
s = 0
for i in range(n):
    a.append(int(fin.readline()))
    s += a[-1]

ans = 0
mn = 10000000000
l = 0
for i in range(n):
    l += a[i]
    if abs(s - 2*l) < mn:
        mn = abs(s - 2*l)
        ans = i + 1

fout.write(str(ans))

fin.close()
fout.close()