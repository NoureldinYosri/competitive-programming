import os;

c = 1; i = 0; p = 1;
while True:
	i += 1;
	os.system("python gen.py")
	os.system("./test < in.in > out.out");
	inf = file("in.in","r");
	ouf = file("out.out","r");
	P = [int(line) for line in inf];
	P.pop(0);
	Z = [line for line in ouf];
	Z = map(int,Z[0].split());
	if len(Z) == 1: continue;
	for i in xrange(len(Z)):
		if P[i] != Z[Z[i] - 1]:
			c = 0;
			break;
	if not c: break;
	inf.close();
	ouf.close();
	if i == p : print "done testing " ,i;
	p *= 10;

if c : print "success";
else : print "fail";
