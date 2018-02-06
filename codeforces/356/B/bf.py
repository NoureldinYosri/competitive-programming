n,m = map(int,raw_input().split());
A = raw_input()*n;
B = raw_input()*m;
assert len(A) == len(B);
print sum(map(lambda x,y:x!=y,A,B));
