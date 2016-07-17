A = [1234567,123456,1234];

def solve(m,i):
	if m <= 0: return m == 0;
	if i == 3: return 0;
	if m%A[i] == 0: return 1;
	if m%A[i] and i == 2: return 0;
	return solve(m - A[i],i) or solve(m,i + 1);

print "YES" if solve(int(raw_input()),0) else "NO"

