#include<bits/stdc++.h>
 
#define REP(i, n) for(int i=0;i<n;i++)
using namespace std;
const int N = 1e5 + 5, M = 1e5 + 5;
 
struct DSU {
    int par[N], sz[N], cntComps, sets[N], pos[N], tail[N], nxt[N];
 
 
    void init(int n) {
        cntComps = n;
        iota(par, par + n, 0);
        fill(sz, sz + n, 1);
        iota(sets, sets + n, 0);
        iota(pos, pos + n, 0);
        iota(tail, tail + n, 0);
        memset(nxt, -1, n * sizeof(nxt[0]));
    }
 
    int operator[](int a) {
        return a == par[a] ? a : par[a] = (*this)[par[a]];
    }
 
    bool operator()(int a, int b) {
        a = (*this)[a];
        b = (*this)[b];
        if (a == b) return false;
        if (sz[a] < sz[b]) swap(a, b);
        par[b] = a;
        sz[a] += sz[b];
        int p = pos[b];
        pos[sets[p] = sets[--cntComps]] = p;
        int &t = tail[a];
        nxt[t] = b;
        t = tail[b];
        return true;
    }
} dsu;
string toString(const DSU&d) {
    stringstream ss;
    ss<<"[";
    REP(i, d.cntComps) {
        ss<<"{";
        for(int u=d.sets[i];~u;u=d.nxt[u])
            ss<<u<<",}"[!~d.nxt[u]];
        ss<<",]"[i+1==d.cntComps];
    }
    return ss.str();
}
 
struct EDGE {
    int from, to, cost;
} edges[M];
 
int es[M], esSz, sts[N], mCost[M], inCost[N], inComingNode[N], vis[N], vid, n;
int used[M],p1[N],p2[N],uid,to[M];
vector<int> del[M];
int chuLiuEdmonds(int root,int esSz=::esSz) {
    memset(mCost, 0, esSz * sizeof(mCost[0]));
    dsu.init(n);
    iota(es, es + esSz, 0);
    int res =0;
    bool notFinished = true;
    uid++;
    int *par=p2,*ppar=p1;
    memset(p1, -1, n * sizeof(p1[0]));
    while (notFinished) {
        inCost[root] = 0;
        inComingNode[root] = -1;
        vis[root] = ++vid;
        for (int i = 0; i < esSz; i++) {
            int e = es[i];
            int f = dsu[edges[e].from];
            int t = dsu[edges[e].to];
            if (f == t or t == root) {
                swap(es[i--] ,es[--esSz]);
                continue;
            }
            int pt=to[e];
            if(ppar[pt]!=e&&~ppar[pt])
                del[e].emplace_back(ppar[pt]);
            int w = edges[e].cost - mCost[e];
            if (vis[t] != vid or w < inCost[t]) {
                vis[t] = vid;
                inCost[t] = w;
                inComingNode[t] = f;
                par[t] = e;
            }
            to[e]=t;
        }
        for (int i = 0; i < esSz; i++) {
            int e = es[i];
            int t = dsu[edges[e].to];
            mCost[e] += inCost[t];
        }
        for (int i = 0; i < dsu.cntComps; i++) {
            int id = dsu.sets[i], u;
            sts[i] = id;
            res += inCost[id];
            if (vis[id] != vid) return -1;
            vis[id] = 0;
            if (id != root) {
                int e = par[id];
                used[e]=uid;
            }
        }
 
        notFinished = false;
        int c = dsu.cntComps;
        for (int i = 0; i < c; i++) {
            ++vid;
            int id = sts[i], u;
            for (u = id; u != root and !vis[u]; u = inComingNode[u]) vis[u] = vid;
            if (vis[u] == vid and u != root) // cycle found
            {
                notFinished = true;
                for (; dsu(u, inComingNode[u]); u = inComingNode[u]);
            }
        }
        root = dsu[root];
        swap(par,ppar);
    }
    for(int i=0;i<::esSz;i++){
        int id = es[i];
        if(used[id]==uid )
            for(auto u:del[id])
              used[u]=0;
    }
 
    return res;
}
 
 
int main() {
 
    freopen("input.txt", "rt", stdin);
    freopen("output.txt", "wt", stdout);
    int t, u, v, c, w, b, tc = 1;
    //canf("%d", &t);
    //  while (t--)
    {
 
        scanf("%d%d", &n, &esSz);
        REP(i, esSz) {
            scanf("%d%d%d", &u, &v, &w);
            edges[i] = {--u, --v, w};
            to[i]=v;
        }
 
 
        auto x = chuLiuEdmonds(0), cnt = 0;
        printf("%d\n", x);
        char *s = "";
        if (~x)
            REP(i, esSz)
                if (used[i]==uid&&edges[i].cost) {
                    printf("%s%d", s, i+ 1), s = " ";
                    cnt++;
                }
        puts("");
 
    }
}
