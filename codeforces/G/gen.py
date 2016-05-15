d = {1: 1,2: 11,3 : 26,4: 28,5 :18,6: 9,7: 3,8: 1}

from math import factorial as fact;
def C(n,k):
	if n < k: return 0;
	return fact(n)/fact(k)/fact(n - k);

#d = {0: 1, 1: 1, 2: 22, 3: 141, 4: 420, 5: 675, 6: 606, 7: 287, 8: 56}
n = 2; #int(raw_input());
r = 0;
for m in d:
	if m:	
		r += d[m] * C(n,m)

print r;

