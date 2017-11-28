def do_inter_scale(a,b,c,d):
    #print a,b,c,d;
    if a > b: a,b = b,a;
    if c > d: c,d = d,c;
    if a > c: a,b,c,d = c,d,a,b;
    return c <= b;

def do_inter(A,B,X,Y):
    if A[0] > B[0]:
        A[0],B[0] = B[0],A[0];
    if X[0] > Y[0]:
        X[0],Y[0] = Y[0],X[0];
    if A[0] > X[0]:
        A,B,X,Y = X,Y,A,B;
    if X[0] > B[0]: return False;
    return do_inter_scale(A[1], B[1], X[1], Y[1]);

n,m = map(int,raw_input().split());
P = [-1] + map(int, raw_input().split());

def get_cnt(A,B):
    ret = 0;
    for i in xrange(1,n+1):
        for j in xrange(i+1,n+1):
            X,Y = [P[i],i],[P[j],j];
            ret += do_inter(A, B, X,Y);
    #        print A,B,X,Y,do_inter(A, B, X, Y)
    return ret;

for i in xrange(m):
    l,d,r,u = map(int,raw_input().split());
    if l > r: l,r = r,l;
    if d > u: d,u = u,d;
    print get_cnt([l,d],[r,u]);
