from tester import *

with open('in.in', 'w') as inf:
	T = randint(1, 10)
	print(T, file = inf)
	for _ in range(T):
		n = randint(1, 10)
		m = randint(1, 10)
		print(n, m, file = inf)
		print(*[randint(1, n) for i in range(m)], file = inf)