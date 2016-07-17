from random import randint
from os import system

def gen():
	A = [randint(1,10**14) for i in xrange(4)];
	f = file("in.in","w");
	f.write("1\n");
	f.write(" ".join([str(x) for x in A]));
	f.close();

#while True:
#	gen();
#	system("./test < in.in");

def solve(A):
	mn = 1 << 50;
	for i in xrange(100):
		for j in xrange(100):
			mn = min(mn,abs(A[0] - A[1] + i*A[2] - j*A[3]));
			if abs(A[0] - A[1] + i*A[2] - j*A[3]) <= abs(A[0] - A[1] + i*A[2] - j*A[3] - A[3]): 
				break;
	return mn;

for i in xrange(25):
	A = [randint(1,10) for i in xrange(4)];
	if A[2]%A[3] == 0 or A[3]%A[2] == 0 : continue;
	x = solve(A);
	if x: print A,x;
