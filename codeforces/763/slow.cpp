#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define all(A) A.begin(),A.end()
#define pb push_back
#define mp make_pair
#define sz(A) ((int)A.size())
typedef std::vector<int> vi;
typedef std::pair<int,int> pi;
typedef std::vector<pi> vp;
typedef long long ll;
#define popcnt(x) __builtin_popcount(x)
#define LSOne(x) ((x) & (-(x)))
#define print(A,t) cerr << #A << ": "; copy(all(A),ostream_iterator<t>(cerr," " )); cerr << endl
#define prArr(A,n,t)  cerr << #A << ": "; copy(A,A + n,ostream_iterator<t>(cerr," " )); cerr << endl
#define PRESTDIO() cin.tie(0),cerr.tie(0),ios_base::sync_with_stdio(0)
#define what_is(x) cerr << #x << " is " << x << endl
#define bit_lg(x) (assert(x > 0),__builtin_ffsll(x) - 1)
const double PI = acos(-1);
template<class A,class B>
std::ostream& operator << (std::ostream& st,const std::pair<A,B> p) {
    st << "(" << p.first << ", " << p.second << ")";
    return st;
}
using namespace std;

const int MAX = 100*1000 + 10;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
vi cand_base {26,29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101, 103, 107, 109, 113, 127, 131, 137, 139};
vi cand_mod {1000001273, 1000001279, 1000001311, 1000001329, 1000001333};
int base[2], mod[2], base_power[2][MAX];
int n;
vi adj[MAX];
int siz[MAX];
 
int add(int a, int b, int m){
    a += b;
    if(a >= m) a -= m;
    if(a < 0) a += m;
    if(a >= m || a < 0) a = (a%m + m)%m;
    return a;
}
int mul(int a, int b, int m){
    return (a*(ll)b)%m;
}
 
void init_hashing(){
    srand(0);
    // srand(time(0));
    shuffle(all(cand_base), rng);
    shuffle(all(cand_mod), rng);
    loop(i,2) base[i] = cand_base[i] + n;
    loop(i,2) mod[i] = cand_mod[i];
    loop(i,2) base_power[i][0] = 1;
    for(int i= 0;i < 2;i++)
        for(int j = 0;j < MAX-1;j++)
            base_power[i][j + 1] = mul(base_power[i][j],base[i],mod[i]);
}
 


struct DS{
    map<pi, int> cnt;
    void add(pi x, int v){
        cnt[x] += v;
        if(cnt[x] == 0) cnt.erase(x);
        else assert(cnt[x] > 0);
    }
};

pi f[MAX];
vector<pair<pi, int>> children[MAX];
DS ds;

pi merge(pi L, pi R, int len){
    pi h;
    h.first = add(mul(L.first, base_power[0][len], mod[0]), R.first, mod[0]);
    h.second = add(mul(L.second, base_power[1][len], mod[1]), R.second, mod[1]);
    return h;
}


pi dfs(int u, int p){
    auto & C = children[u];
    for(int v : adj[u]) if(v != p){
        auto tmp = dfs(v, u);
        C.emplace_back(tmp, v);
        siz[u] += siz[v];
    }
    sort(all(C));
    f[u] = pi(0, 0);
    siz[u] = 1;
    for(auto [h, v] : C){
        f[u] = merge(f[u], h, siz[v]);
        siz[u] += siz[v];
    }
    f[u] = merge(f[u], pi(siz[u], siz[u]), 1);
    
    ds.add(f[u], 1);
    return f[u];
}

pi ans;

void dfs(int u, int p, pi fp){
    pi old = f[u];
    ds.add(old, -1);
    ans = max(ans, pi(ds.cnt.size(), -u));
    
    auto & C = children[u];
    if(p){
        C.emplace_back(fp, p);
        sort(all(C));
    }
    
    int m = sz(C);

    
    loop(i, m){
        auto [_, v] = C[i];
        if(v == p) continue;

        pi tmp (0, 0);
        int S = 0;
        for(auto [ht, t] : C) if(t != v) {
            int s = siz[t];
            if(t == p) s = n-siz[u];
            S += s;
            tmp = merge(tmp, ht, s);
        }
        S++;
        assert(S == n-siz[v]);
        tmp = merge(tmp, pi(S, S), 1);

        ds.add(tmp, 1);
        if(v != p) dfs(v, u, tmp);
        ds.add(tmp, -1);    
    }
    
    
    ds.add(old, 1);
}

int main(){
#ifdef HOME
    freopen("in.in", "r", stdin);
#endif
    scanf("%d", &n);
    loop(e, n-1){
        int a, b; scanf("%d %d", &a, &b);
        adj[a].pb(b);
        adj[b].pb(a);
    }
    init_hashing();
    dfs(1, 0);
    ans = pi(-1, 0);
    dfs(1, 0, pi(0, 0));
    cout << -ans.second << endl;
    //cerr << ans << endl;
    return 0;
}
