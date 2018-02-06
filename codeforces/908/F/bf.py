n = int(raw_input());
X = [0 for i in xrange(n)];
C = [0 for i in xrange(n)];
for i in xrange(n):
    X[i],C[i] = raw_input().split();
    X[i] = int(X[i]);

debug = False;

def can_connect(i,j):
    global C;
    if C[i] == 'G' or C[j] == 'G': return True;
    return C[i] == C[j];



def dfs(u,c,P,vis):
    global C;
    vis[u] = True;
    adj = [];
    if u < len(P): adj.append(P[u]);
    for i in xrange(len(P)):
        if P[i] == u:
            adj.append(i);
    for v in adj:
        if v == -1: continue;
        if vis[v]: continue;
        if C[v] != 'G' and C[v] != c:
            continue;
        dfs(v,c,P,vis);


def valide(c,P):
    global C,debug;
    j = -1;
    for i in xrange(n):
        if C[i] == c:
            j = i;
    if j == -1: return True;

    vis = [False for i in xrange(n)]
    dfs(j,c,P,vis);
    if debug: print j,vis;
    for i in xrange(n):
        if C[i] == c or C[i] == 'G':
            if not vis[i]:
                return False;
    return True;
    
def valid(P):
    global debug;
    for c in "RGB":
        r = valide(c,P);
        if debug: 
            print P,c,r
        if not r:
            return False;

    return True;


dp = {};
def solve(P):
    global n,X,C,dp,debug;
    debug = False;
    if len(P) == n-1:
#         if P == [2,2,3]: 
#             debug = True;
        r = valid(P)
        if debug:
           print P,r
           debug = False;
        if not r : return 10**18;
        return 0;
    t = tuple(P)
    if t in dp: return dp[t];
    
    ret = 10**18;
    i = len(P);
    for j in xrange(-1,n):
        if j == -1 or can_connect(i,j):
            P.append(j);
            c = solve(P);
            if j != -1: c += abs(X[j] - X[i]);
            ret = min(ret,c);
            P.pop();
    dp[t] = ret;
    return ret;

print solve([])