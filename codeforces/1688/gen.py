from tester import *

with open('in.in', 'w') as inf:
	T = randint(1, 5)
	print(T, file=inf)
	for _ in range(T):
		n = randint(1, 5)
		print(n, file = inf)
		print(*[randint(1, 10**9) for i in range(n)], file = inf)