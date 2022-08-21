from math import lcm

ctr = tot = 0
for c in range(1, 100):
    for b in range(1, c):
        for a in range(1, b):
            if lcm(a, b, c) < a + b + c:
                # print(f'{a=} {b=} {c=}')
                assert c%a == 0 and c%a == 0, f'{a=} {b=} {c=}'
                ctr += 1
            # else:
            #     assert not(c%a == 0 and c%a == 0), f'fail {a=} {b=} {c=}'
            tot += 1

print(f'{ctr=}/{tot=} = {ctr/tot}')