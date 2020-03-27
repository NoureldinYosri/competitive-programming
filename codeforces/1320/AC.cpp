#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
#define fi first
#define se second
#define all(x) (x).begin() , (x).end()
#define rall(x) (x).rbeign() , (x).rend()
#define len(x) (int)(x).size()
#define pb push_back
#define fast_io ios_base::sync_with_stdio(0) , cin.tie(0) , cout.tie(0)
 
using namespace std;
using namespace __gnu_pbds;
 
 
typedef tree<int,null_type,less<int>,rb_tree_tag,tree_order_statistics_node_update>ordered_set;
typedef long long ll;
typedef long double ld;
const int N = 2e5 + 10;
const int LG = 25;
const int inf = 1e9;
vector < int > g[N];
int pred[N] , up[N][LG], tin[N] , tout[N] ,  T = 0 , D[N];
void dfs(int v , int p, int d){
    D[v] = d;
    tin[v] = T++;
    pred[v] = p;
    for(auto u : g[v]){
        if(u != p){
            dfs(u , v , d + 1);
        }
    }
    tout[v] = T-1;
}
void build_lca(int n){
    for(int i = 0 ; i < n; ++i)
        up[i][0] = pred[i];
    for(int st = 1;  st < LG; ++st){
        for(int i = 0 ; i < n; ++i){
            up[i][st] = up[up[i][st-1]][st-1];
        }
    }
}
bool anc(int u , int v){
    return ((tin[u] <= tin[v]) && (tout[u] >= tout[v]));
}
int get_lca(int u , int v){
    if(anc(u , v))return u;
    if(anc(v , u))return v;
    for(int st = LG - 1; st >= 0 ; --st){
        if(!anc(up[u][st] , v)){
            u = up[u][st];
        }
    }
    return up[u][0];
}
int path(int u , int v){
    int lca = get_lca(u , v);
    return D[u]+D[v]-2*D[lca];
}
bool cmp(const int &a, const int &b){
    return tin[a] < tin[b];
}
int CEIL(int x , int y){
    return x / y + (x % y > 0);
}
vector < vector < int > > Tree;
vector < int > vert;
vector < pair < int , int > > virus;
vector < int > Vir;
vector < int > Time;
/// ok let's from subtree
void upd(int v , int ind){
//    cerr << " UPD " <<  vert[v] << ' ' << ind << '\n';
    int stage = CEIL(path(virus[ind].fi , vert[v]),virus[ind].se);
    if(stage<Time[v]||(stage==Time[v]&&ind<Vir[v]&&stage!=0)){
        Vir[v] = ind;
        Time[v] = stage;
    }
}
void sub(int v){
    for(auto u : Tree[v]){
        sub(u);
        if(Time[u] != inf)
        upd(v , Vir[u]);
    }
}
void over(int v, int best){
    if(best!=inf)
    upd(v , best);
    if(Time[v] != inf)
    best = Vir[v];
    for(auto u : Tree[v]){
        over(u , best);
    }
}
int ans[N] , pos[N];
signed main(){
    fast_io;
    int n;cin >> n;
    for(int i = 0 ; i < n - 1; ++i){
        int u , v;cin >> u >> v;
        --u , --v;
        g[u].pb(v);
        g[v].pb(u);
    }
    dfs(0 , 0 , 0);
    build_lca(n);
    int q;cin >> q;
    while(q--){
        int k , m;cin >> k >> m;
        vert.clear() , Tree.clear() , Vir.clear() , Time.clear() , virus.clear();
        virus.resize(k);
 
 
        vector < int > input(m);
        for(int i = 0 ; i < k;  ++i){
            int u , s;cin >> u >> s;
            virus[i] = {u - 1 , s};
            vert.pb(u - 1);
        }
        for(int i = 0 ; i < m; ++i){
            int x;cin >> x;
            input[i] = x - 1;
            vert.pb(x - 1);
        }
        sort(all(vert) , cmp);
        for(int i = 0 ; i < m + k - 1; ++i){
            vert.pb(get_lca(vert[i] , vert[i + 1]));
        }
        sort(all(vert));
        vert.erase(unique(all(vert)) , vert.end());
        sort(all(vert) , cmp);
        Tree.resize(len(vert));
        Vir.resize(len(vert));
        Time.resize(len(vert) , inf);
 
 
        for(int i = 0 ; i < len(vert); ++i)
            pos[vert[i]] = i;
        for(int i = 0 ; i < k; ++i){
            upd(pos[virus[i].fi] , i);
        }
        vector < int > stac;
        for(int i = 0 ; i < len(vert); ++i){
            while(!stac.empty() && tout[vert[stac.back()]] < tin[vert[i]])
                stac.pop_back();
            if(!stac.empty()){
                Tree[stac.back()].pb(i);
            }
            stac.pb(i);
        }
        sub(0);
        over(0, inf);
        for(int i = 0 ; i < len(vert);++i){
            ans[vert[i]] = Vir[i];
        }
        for(int i = 0 ; i < m; ++i){
            cout << ans[input[i]] + 1 << ' ';
        }
        cout << '\n';
    }
    return 0;
}
