n = int(raw_input())
A = map(int, raw_input().split());
ans = 0;
while len(A):
    ans += 1;
    a = A.pop(0);
    if len(A) == 0 or a <= min(A): continue;
    A.append(a);

print ans;