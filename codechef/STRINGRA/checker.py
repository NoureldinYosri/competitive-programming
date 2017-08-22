def read_edges(name):
    f = file(name,"r");
    F = [l for l in f];
    f.close();
    F.pop(0);
    F.pop(0);
    F.sort();
    ret = map(lambda x:tuple(map(int,x.split())), F);
    ret.sort();
    return ret;

def read_sol(name):
    f = file(name,"r");
    F = [l for l in f];
    f.close();
    A = map(int,F[0].split());
    return A;

def get_subs(A):
    subs = {};
    subs[tuple()] = 0;
    n = len(A);
    for msk in xrange(1 << n):
        B = [];
        lst = 0;
        for i in xrange(n):
            if msk & (1 << i):
                B.append(A[i]);
                lst = i + 1;
        B = tuple(B);
        if B not in subs: subs[B] = lst;
        subs[B] = min(subs[B],lst);
    return subs;
    
def is_valid(A,B):
    if len(A) + 1 != len(B): return False;
    return A == B[:-1];

def get_E(subs):
    tot = list(subs.keys());
    tot.sort(key=lambda x:len(x));
    E = [];
    for j in xrange(len(tot)):
        for i in xrange(j):
            if is_valid(tot[i],tot[j]):
                E.append((subs[tot[i]],subs[tot[j]]));
    S = set();
    for e in E:
        S.add(tuple(e));
    E = list(S);
    E.sort();
    return E;

def create(A):
    return get_E(get_subs(A));

def verify(iE,A):
    if A[0] == -1: return "unknown";
    E = create(A);
    return E == iE;


def validate(input,output):
    E = read_edges(input);
    A = read_sol(output);
    ret = verify(E, A);
    if not ret:
        print "A is " ,A,"produces",create(A);
        print "as oppossed to ",E;
    return ret;