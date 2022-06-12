n = int(input())
hist = {}
for i in range(n):
    line = input().replace(' ', '')
    for j in line:
        if j in hist:
            hist[j] += 1
        else:
            hist[j] = 1
for i in hist:
    print(i, hist[i])
