from random import randint

print(100)
print('1 2 3 4 5 6 7 8')
print('1 2 3 4 4 5 6 9')
print('1 3 2 3 4 3 5 2')
for i in range(1100, 10701, 100):
    t = i
    for j in range(8):
        print(t % 6, end=' ')
        t //= 6
    print()