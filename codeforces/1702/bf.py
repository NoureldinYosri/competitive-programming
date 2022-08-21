
def tc():
    n = int(input())
    pairs = [tuple(map(int, input().split())) for i in range(n)]
    for msk in range(1 << n):
        S = [set() for i in range(2)]
        good = True
        for i in range(n):
            c = (msk >> i) & 1
            for v in pairs[i]:
                if v in S[c]:
                    good = False
                    break
                S[c].add(v)
            if not good:
                break
        if good:
            print("YES")
            return
    print("NO")

for _ in range(int(input())):
    tc()
