
def answer(n):
	ans = 0;
	B = [1 if c == '1' else 0 for c in bin(int(n))[2:]];
	while len(B) != 1:
		while B[-1] == 0:
			ans += 1;
			B.pop();
		if len(B) == 1: break;
		ans += 1;
		c1 = len(B);
		c2 = len(B);
		for i in xrange(1,len(B)):
			if B[len(B) - 1 - i]:
				c1 = i;
				break;
		r = 1;
		for i in xrange(len(B)):
			t = B[len(B) - 1 - i];
			if r:
				if t: r = 0;
				else:
					t = 1;
					r = 0;
			if t: 
				c2 = i;			
				break;
		if c1 <= c2: B[-1] = 0;
		else:
			r = 1;
			for i in xrange(len(B)-1,-1,-1):
				if B[i]: B[i] = 0;
				else:
					B[i] = 1; 
					r = 0;
					break;
			if r: B.insert(0,1);
	return ans;

