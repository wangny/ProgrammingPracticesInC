caseCount = int(input())
for case in range(caseCount):
  [N, K] = input().split(' ')
  sold = input().split(' ')
  total = 0
  for i in range(C):
    [p, c] = input().split(' ')
    cards[int(p)] = int(c)
    prime.append(int(p))
    total += int(p)*int(c)

  prime.sort()
  ans = find(prime, cards, total, 1)

  print(f'Case #{case+1}: {ans}')