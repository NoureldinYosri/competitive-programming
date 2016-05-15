def mul(A,B,m):
	C = [[0,0],[0,0]];
	for i in range(2):
		for j in range(2):
			for k in range(2):
				C[i][j] = (C[i][j] + A[i][k] * B[k][j])%m;
	return C;

def EXP(A,n,m):
	if n == 0:
		A = [[1%m,0],[0,1%m]];
		return A;
	if n == 1: return A;
	B = EXP(mul(A,A,m),n >> 1,m);
	if n & 1: B = mul(A,B,m);
	return B;

T = int(raw_input());
while T:
	T -= 1;
	a,b,n,m = map(int,raw_input().split());
	if n == 0: print 1%m;
	else :
		A = EXP([[a,1],[0,1]],n ,m);
		ans = A[0][0] + A[0][1] * b;
		#print A[0],A[1];
		ans %= m;
		print ans;
