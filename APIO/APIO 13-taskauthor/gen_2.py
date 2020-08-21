# Description: 100 nodes; 1100 edges; Straight line from 99 to 0 with some self edges at 0

print(100)
print(1011, end=' ')
for i in range(1011):
    print(0, 1, end=' ')
print()
for i in range(1, 100):
    print(1, i - 1, 1)

print(10)
for i in range(10):
    print(99, 0)