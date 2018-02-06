n,m = map(int, raw_input().split())
A = map(int, raw_input().split())
D = {0:tuple(A)};
time_stamp = 0;
for i in xrange(m):
    arg = raw_input().split();
    c = arg.pop(0);
    if c == 'C':
        l,r,d = map(int, arg);
        for i in xrange(l-1,r):
            A[i] += d;
        time_stamp += 1;
        D[time_stamp] = tuple(A);
        
    elif c == 'Q':
        l,r = map(int, arg);
        ans = 0;
        for i in xrange(l-1,r):
            ans += A[i];
        print ans;
    elif c == 'H':
        l,r,t = map(int, arg);
        B = D[t];
        ans = 0;
        for i in xrange(l-1,r):
            ans += B[i];
        print ans;
    else:
        t = map(int, arg)[0];
        A = list(D[t]);

