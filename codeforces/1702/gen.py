from tester import *

with open('in.in', 'w') as inf:
	T = randint(1, 10)
	print(T, file = inf)
	for _ in range(T):
		n = 2*randint(1, 5)
		print(n, file = inf)
		A = [i+1 for i in range(n)]
		B = [i+1 for i in range(n)]
		shuffle(A)
		shuffle(B)
		for a, b in zip(A, B):
			print(a, b, file=inf)
