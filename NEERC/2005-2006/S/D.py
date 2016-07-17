n = int(raw_input());
A = [0 for i in range(n)];
for i in range(n):
	A[i] = int(raw_input());

A.sort();

c = 0;
for i in range(n - 2):
	if A[i] + A[i + 1] > A[i + 2]:
		print A[i],A[i + 1],A[i + 2];
		c = 1;
		break;
if not c:
	print 0,0,0;
