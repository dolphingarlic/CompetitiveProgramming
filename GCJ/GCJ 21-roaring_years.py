t = int(input())
for test in range(1, t + 1):
    y = input()
    yi = int(y)
    ans = 10 ** 50
    curr_start = 0
    curr_pow = 1
    for i in y:        
        curr = curr_start * (10 ** len(str(curr_start + 1))) + curr_start + 1
        # Case 1: Try as is
        cp = curr_start + 2
        while curr <= yi:
            curr = curr * (10 ** len(str(cp))) + cp
            cp += 1
        ans = min(ans, curr)

        curr = (curr_start + 1) * (10 ** len(str(curr_start + 2))) + curr_start + 2
        # Case 2: Plus one
        cp = curr_start + 3
        while curr <= yi:
            curr = curr * (10 ** len(str(cp))) + cp
            cp += 1
        ans = min(ans, curr)

        cpp = curr_pow
        for j in range(min(curr_pow, 10)):
            curr = cpp * (10 ** len(str(cpp + 1))) + cpp + 1
            # Case 3:
            cp = cpp + 2
            while curr <= yi:
                curr = curr * (10 ** len(str(cp))) + cp
                cp += 1
            ans = min(ans, curr)
            cpp -= 1
        
        curr_start = curr_start * 10 + int(i)
        curr_pow *= 10
    
    curr = curr_start * (10 ** len(str(curr_start + 1))) + curr_start + 1
    # Case 1: Try as is
    cp = curr_start + 2
    while curr <= yi:
        curr = curr * (10 ** len(str(cp))) + cp
        cp += 1
    ans = min(ans, curr)

    curr = (curr_start + 1) * (10 ** len(str(curr_start + 2))) + curr_start + 2
    # Case 2: Plus one
    cp = curr_start + 3
    while curr <= yi:
        curr = curr * (10 ** len(str(cp))) + cp
        cp += 1
    ans = min(ans, curr)

    cpp = curr_pow
    for j in range(min(curr_pow, 10)):
        curr = cpp * (10 ** len(str(cpp + 1))) + cpp + 1
        # Case 3:
        cp = cpp + 2
        while curr <= yi:
            curr = curr * (10 ** len(str(cp))) + cp
            cp += 1
        ans = min(ans, curr)
        cpp -= 1
    
    print(f'Case #{test}: {ans}')
