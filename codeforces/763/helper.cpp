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

pi dfs(int u, int p){
    f[u] = pi(0, 0);
    auto & C = children[u];
    for(int v : adj[u]) if(v != p){
        C.emplace_back(dfs(v, u), v);
    }
    sort(all(C));
    for(auto [h, v] : C){
        f[u].first = mul(f[u].first, base[0], mod[0]);
        f[u].first = add(f[u].first, h.first + 1, mod[0]);

        f[u].second = mul(f[u].second, base[1], mod[1]);
        f[u].second = add(f[u].second, h.second + 1, mod[1]);
    }
    ds.add(f[u], 1);
    return f[u];
}

pi ans;

void dfs(int u, int p, pi fp){
    pi old = f[u];
    ds.add(old, -1);
    ans = max(ans, pi(ds.cnt.size(), u));
    
    auto & C = children[u];
    if(p){
        C.emplace_back(fp, p);
        sort(all(C));
    }
    
    int m = sz(C);
    vp suff(m);
    for(int i = m-1; i > 0; i--){
        pi & H = suff[i - 1];
        H = suff[i];
        pi h = C[i].first;
        h.first = add(h.first, 1, mod[0]);
        h.second = add(h.second, 1, mod[1]);
        
        h.first = mul(h.first, base_power[0][m-i-1], mod[0]);
        h.second = mul(h.second, base_power[1][m-i-1], mod[1]);
        
        H.first = add(H.first, h.first, mod[0]);
        H.second = add(H.second, h.second, mod[1]);
    }
    
    pi H(0, 0);
    
    loop(i, m){
        pi newH (H);
        newH.first = mul(newH.first, base_power[0][m-1-i], mod[0]);
        newH.second = mul(newH.second, base_power[1][m-1-i], mod[1]);
        newH.first = add(newH.first, suff[i].first, mod[0]); 
        newH.second = add(newH.second, suff[i].second, mod[1]);
        
        ds.add(newH, 1);
        auto [h, v] = C[i];
        if(v != p) dfs(v, u, newH);
        ds.add(newH, -1);   
        
        H.first = mul(H.first, base[0], mod[0]);
        H.first = add(H.first, h.first + 1, mod[0]);

        H.second = mul(H.second, base[1], mod[1]);
        H.second = add(H.second, h.second + 1, mod[1]);
    }
    
    
    ds.add(old, 1);
}

int main(int argc, char **argv){
    freopen("in.in", "r", stdin);
    assert(argc > 1);
    scanf("%d", &n);
    loop(e, n-1){
        int a, b; scanf("%d %d", &a, &b);
        adj[a].pb(b);
        adj[b].pb(a);
    }
    init_hashing();
    int root; sscanf(argv[1], "%d", &root);
    dfs(root, 0);
    cout << ds.cnt.size() << endl;
    return 0;
}
