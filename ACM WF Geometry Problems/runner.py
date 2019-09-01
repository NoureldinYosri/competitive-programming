import sys
from os import system,walk

code = sys.argv[1]
path = sys.argv[2]


def read(fname):
	F = open(fname,'r')
	f = [l.strip() for l in F]
	F.close()
	return f

system('g++ {} -std=c++11 -o test'.format(code))

for _,_,fnames in walk(path):
	break

ifnames = list(filter(lambda s: ".in" in s,fnames))
ofnames = list(filter(lambda s: ".ans" in s,fnames))
ifnames.sort()
ofnames.sort()
AC = True
for (ifname,ofname) in zip(ifnames,ofnames):
	print('running on',ifname)
	v = system("./test < {}/{} > out.out".format(path,ifname))
	if v:
		AC = False
		print('non zero exit code on',ifname)
		continue
	ans = read("out.out")
	correct = read("{}/{}".format(path,ofname))
	if len(ans) != len(correct):
		AC = False
		print('unequal number of tokens')
		continue
	yes = True
	for i in range(len(ans)):
		yes &= ans[i] == correct[i]
	if not yes:
		print ('WA on',ifname)
		AC = False
	else:
		print('passed on',ifname,':)')
print('AC :D' if AC else "WA :(")
