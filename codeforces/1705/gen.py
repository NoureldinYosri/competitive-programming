from tester import *

with open('in.in', 'w') as inf:
    T = randint(1, 5)
    print(T, file = inf)
    for _ in range(T):
        n = randint(3, 10)
        print(n, file = inf)
        for i in range(2):
            print(create_str(n, '01'), file = inf)
