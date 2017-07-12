import os;

for i in xrange(26):
	s = str(i);
	if i < 10: s = "0" + s;
	name = "/home/noureldin/Desktop/workspace/competitive-programming/kattis/Jewel\ Thief/data/secret/thief-10%s"%s;
	os.system("./test < %s.in > out.out"%name);
	os.system("diff %s.ans out.out > err.log"%name);
	f = file("err.log");
	F = [l for l in f]
	f.close();
	if len(F):
		print "failed on test",i;
		break;
	print "passed case",i;
