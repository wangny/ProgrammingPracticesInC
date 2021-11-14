def find(prime, cards, total, product):
  if total == product:
    return product
  if total < product:
    return 0
  poss = []
  for p in prime:
    if cards[p]>0:
      cards[p] -= 1
      a = find(prime, cards, total-p, int(product*p))
      cards[p] += 1
      if a>0:
        poss.append(a)
  if len(poss):
    return max(poss)
  return 0


caseCount = int(input())
for case in range(caseCount):
  C = int(input())
  cards = {}
  prime = []
  total = 0
  for i in range(C):
    [p, c] = input().split(' ')
    cards[int(p)] = int(c)
    prime.append(int(p))
    total += int(p)*int(c)

  prime.sort()
  ans = find(prime, cards, total, 1)

  print(f'Case #{case+1}: {ans}')