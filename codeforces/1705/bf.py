
def bfs(src, target):
    D = {src: 0}
    q = [src]
    while len(q):
        s = q.pop(0)
        if s == target: return D[s]
        d = D[s]
        s = [c for c in s]
        for i in range(1, len(s) - 1):
            if s[i - 1] == s[i + 1]: continue
            old = s[i]
            s[i] = '1' if old == '0' else '0'
            t = ''.join(s)
            if t not in D:
                D[t] = d + 1
                q.append(t)
            s[i] = old
    return -1

def tc():
    n = input()
    s1 = input().strip()
    target = input().strip()
    print(bfs(s1, target))

for _ in range(int(input())):
    tc()
