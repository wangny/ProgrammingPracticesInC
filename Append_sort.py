import math
caseCount = int(input())
for case in range(caseCount):
  numCount = int(input())
  nums = input().split(' ')
  count = 0
  for i in range(1, numCount):
    if int(nums[i]) > int(nums[i-1]):
      continue
    add = max(1, len(nums[i-1]) - len(nums[i]))
    tobe = str(max(int(nums[i]+'0'*add), int(nums[i-1])+1))
    if tobe[:len(nums[i])] == nums[i]:
      count += len(tobe) - len(nums[i])
      nums[i] = tobe
    else:
      add = math.ceil(math.log(int(tobe)/int(nums[i]), 10))
      count += add
      nums[i] += '0'*add

  print(f'Case #{case+1}: {count}')