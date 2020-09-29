#pragma GCC optimize ("O3")
#include<bits/stdc++.h>
#define ll long long
#define S second
#define F first
#define neig(head, u, e, v) for(int e = head[u], v ; ~e and (v = to[e], 1) ; e = nxt[e])

using namespace std;

const int N = 1e5 + 5, M = N * 2;

int head[N], to[M], nxt[M], n, ne;

inline void init(int n)
{
    ne = 0;
    memset(head, -1, n * sizeof(head[0]));
}

inline void addEdge(int f, int t)
{
    nxt[ne] = head[f];
    to[ne] = t;
    head[f] = ne++;
}

inline void addBiEdge(int f, int t)
{
    addEdge(f, t);
    addEdge(t, f);
}

int sz[N], par[N], heavyCh[N], dep[N];

inline void calcSz(int u)
{
    int mx = 0;
    heavyCh[u] = -1;
    sz[u] = 1;
    neig(head, u, e, v)
    {
        if(v == par[u]) continue;
        par[v] = u;
        dep[v] = dep[u] + 1;
        calcSz(v);
        sz[u] += sz[v];
        if(sz[v] > mx) mx = sz[v], heavyCh[u] = v;
    }
}

int indexToNode[N], nodeToIndex[N], chainSz[N], chainHead[N], curT, val[N];

inline void hld(int u, int ch)
{
    chainHead[u] = ch;
    if(u == ch) chainSz[ch] = 0;
    chainSz[ch]++;
    indexToNode[nodeToIndex[u] = curT++] = u;
    if(~heavyCh[u]) hld(heavyCh[u], ch);
    neig(head, u, e, v)
    {
        if(par[u] == v or heavyCh[u] == v) continue;
        hld(v, v);
    }
}

inline void hld(int root)
{
    curT = 0;
    dep[root] = 0;
    par[root] = -1;
    calcSz(root);
    hld(root, root);
}

struct node
{
    int fs, lt, df, lazy;
    void setLazy(int val)
    {
        lazy += val;
        fs += val;
        lt += val;
    }
}nodes[1<<17];

inline void pushDown(int ni, int ns, int ne)
{
    if(!nodes[ni].lazy or ns == ne) return;
    int lf = ni * 2 + 1, rt = lf + 1;
    nodes[lf].setLazy(nodes[ni].lazy);
    nodes[rt].setLazy(nodes[ni].lazy);
    nodes[ni].lazy = 0;
}

inline node merge(const node &a, const node &b)
{
    int d = a.lt - b.fs;
    int g = __gcd(__gcd(a.df, b.df), d);
    return {a.fs, b.lt, g};
}

inline void build(int ni = 0, int ns = 0, int ne = n - 1)
{
    if(ns == ne)
    {
        int value = val[indexToNode[ns]];
        nodes[ni] = {value, value, 0, 0};
        return;
    }
    int lf = ni * 2 + 1, rt = lf + 1, mid = ns + (ne - ns) / 2;
    build(lf, ns, mid);
    build(rt, mid + 1, ne);
    nodes[ni] = merge(nodes[lf], nodes[rt]);
}

inline void update(int qs, int qe, int val, int ni = 0, int ns = 0, int ne = n - 1)
{
    pushDown(ni, ns, ne);
    if(qs > ne or qe < ns) return;
    if(ns >= qs and ne <= qe)
    {
        nodes[ni].setLazy(val);
        return;
    }
    int lf = ni * 2 + 1, rt = lf + 1, mid = ns + (ne - ns) / 2;
    update(qs, qe, val, lf, ns, mid);
    update(qs, qe, val, rt, mid + 1, ne);
    nodes[ni] = merge(nodes[lf], nodes[rt]);
}

inline node query(int qs, int qe, int ni = 0, int ns = 0, int ne = n - 1)
{
    pushDown(ni, ns, ne);
    if(qs > ne or qe < ns) return {0, 0, 0, 0};
    if(ns >= qs and ne <= qe) return nodes[ni];
    int lf = ni * 2 + 1, rt = lf + 1, mid = ns + (ne - ns) / 2;
    return merge(query(qs, qe, lf, ns, mid), query(qs, qe, rt, mid + 1, ne));
}

inline node get(int u, int v)
{
    node retU = {0, 0, 0, 0}, retV = {0, 0, 0, 0};
    while(chainHead[u] != chainHead[v])
    {
        if(dep[chainHead[u]] < dep[chainHead[v]]) swap(u, v), swap(retU, retV);
        node temp = query(nodeToIndex[chainHead[u]], nodeToIndex[u]);
        retU = merge(temp, retU);
        u = par[chainHead[u]];
    }
    if(dep[u] > dep[v]) swap(u, v), swap(retU, retV);
    node temp = query(nodeToIndex[u], nodeToIndex[v]);
    retV = merge(temp, retV);
    swap(retV.fs, retV.lt);
    return merge(retV, retU);
}

inline void add(int u, int v, int val)
{
    while(chainHead[u] != chainHead[v])
    {
        if(dep[chainHead[u]] < dep[chainHead[v]]) swap(u, v);
        update(nodeToIndex[chainHead[u]], nodeToIndex[u], val);
        u = par[chainHead[u]];
    }
    if(dep[u] > dep[v]) swap(u, v);
    update(nodeToIndex[u], nodeToIndex[v], val);
}

inline int readInt(){
    char c=getchar();
    int sign=1,ret=0;
    while(isspace(c))	c=getchar();
    if(c=='-')	sign=-1,c=getchar();
    while(isdigit(c)) ret*=10,ret+=c-'0',c=getchar();
    return ret*sign;
}


int main()
{
//    freopen("input.in","r",stdin);
    int u, v, x, m, a, b, c;
    n = readInt();
    init(n);
    for(int i = 0 ; i < n - 1 ; i++)
    {
        u = readInt();
        v = readInt();
        addBiEdge(u, v);
    }
    for(int i = 0 ; i < n ; i++) val[i] =  readInt();
    hld(0);
    build();
    int q, temp;
    char ch;
    q = readInt();
    while(q--)
    {
        while(ch = getchar(), isspace(ch));
        u = readInt();
        v = readInt();
        if(ch == 'F')
        {
            auto ret = get(u, v);
            printf("%d\n", abs(__gcd(ret.fs, ret.df)));
        }
        else
        {
            temp = readInt();
            add(u, v, temp);
        }
    }
    return 0;
}