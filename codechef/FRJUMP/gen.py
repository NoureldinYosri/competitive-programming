from random import randint
from os import system

MAX = 1000
MAXN = 10**9;

n = r = A = None;
def CreateTest():
	global n,r,A;
	n = randint(1,MAX);
	A = [randint(1,MAXN) for i in xrange(n)];
	r = randint(1,MAX);	
	B = [str(x) for x in A];

	f = file("in.in","w");
	f.write(str(n) + "\n");
	f.write(" ".join(B) + "\n");
	f.write("1\n2 " + str(r));
	f.close();

def solve():
	tot = 1;
	p = 0;
	while p < n:
		tot *= A[p];
		p += r;
	return [int(str(tot)[0]),tot%(10**9 + 7)]


def isCorrect():
	system("./test < in.in > out.out");
	f = file("out.out");
	f = [l for l in f];
	a,b = map(int,f[0].split());
	c,d = solve();
	if a != c or b != d:
		print a,b,c,d;
		return 0;
	return 1;

t = 1;
while True:
	CreateTest();
	print A,n,r;
	if not isCorrect():
		print "found"
		break;
	print "Done %d"%t
	t += 1;


