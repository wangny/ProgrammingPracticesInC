#CJ -> X
#JC -> Y

caseCount = int(input())
for case in range(caseCount):
  [X, Y, mural] = input().split(' ')
  prev = ''
  xCount = yCount = 0
  for i in range(len(mural)-1, -1, -1):
    if mural[i] == 'C':
      if prev == 'J':
        xCount += 1
      prev = 'C'
    elif mural[i] == 'J':
      if prev == 'C':
        yCount += 1
      prev = 'J'

  cost = int(X) * xCount + int(Y)* yCount
  print(f'Case #{case+1}: {cost}')