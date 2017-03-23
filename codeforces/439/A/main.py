n,d = map(int,raw_input().split());
A = map(int,raw_input().split());
if sum(A) + (n - 1)*10 > d:
	print -1;
else:
	print (d - sum(A))/5;
