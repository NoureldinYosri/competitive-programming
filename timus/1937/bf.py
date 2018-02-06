U = raw_input();
V = raw_input();
m = len(U);
n = len(V);
for i in xrange(m):
    for j in xrange(n):
        T = list(U[i:] + U[:i] + V[j:] + V[:j]);
#         print T;
        O = [x for x in T];
        O.reverse();
        if T == O:
            print "Yes"
            print i + 1,j + 1;
            exit(0)
            
print "No"