a, b = map(int, input().split())
for i in range(a, b + 1):
    s = str(i)
    if s == s[::-1]:
        print('Palindrome!')
    else:
        print(i)
