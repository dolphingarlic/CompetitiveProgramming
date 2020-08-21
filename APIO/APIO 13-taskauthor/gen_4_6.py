# Description: Triangles with negative edges to get exponential Dijkstra complexity

print(33)
print(0)
print(1, 0, 1)
print(1, 1, 1)
for i in range(2, 31, 2):
    print(1, i, -2 * (2**(i//2)))
    print(2, i + 1, 2**(i//2), i, 0)

print(7)
for i in range(7):
    print(32, 0)
