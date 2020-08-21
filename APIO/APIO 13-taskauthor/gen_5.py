# Description: 300 nodes; 347 edges; Straight line from 299 to 0 with some self edges at 0

print(300)
print(48, end=' ')
for i in range(48):
    print(0, 1, end=' ')
print()
for i in range(1, 300):
    print(1, i - 1, 1)

print(10)
for i in range(10):
    print(299, 0)