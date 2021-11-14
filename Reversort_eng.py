
def getList(N, C):
  if C < N-1:
    return None

  toReverse = []
  for i in range(N, 1, -1):
    if C < 0:
      break
    if i > C - (i-2):
      C -= 1
      continue
    toReverse.insert(0, i)
    C -= i

  if C != 0:
    return None

  num = [i+1 for i in range(N)]
  for i in toReverse:
    tmp = num[N-i:]
    tmp.reverse()
    num[N-i:] = tmp
  return num

caseCount = int(input())

for case in range(caseCount):
  [N, C] = input().split(' ')
  ans = getList(int(N), int(C))
  if ans is None:
    print(f'Case #{case+1}: IMPOSSIBLE')
  else:
    out = ' '.join([str(elem) for elem in ans])
    print(f'Case #{case+1}: {out}')
