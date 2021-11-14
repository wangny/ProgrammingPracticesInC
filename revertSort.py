def getCost(num):
  cost = 0
  for i in range(len(num)-1):
    j = num.index( min(num[i:]), i)+1
    tmp = num[i:j]
    tmp.reverse()
    num[i:j] = tmp
    cost += j-i
  return cost

caseCount = int(input())

for case in range(caseCount):
  numCount = int(input())
  num = [ int(i) for i in input().split(' ')]
  cost = getCost(num)
  print(f'Case #{case+1}: {cost}')
