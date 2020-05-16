nums = list(map(int, input().split()))
n = int(input())

sm = sum(nums)
for i in range(n - len(nums)):
    nums[i % len(nums)], sm = sm, 2 * sm - nums[i % len(nums)]
print(nums[(n - 1) % len(nums)])