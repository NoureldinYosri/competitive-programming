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


vector<vi> adj, parents;
vi in_deg, out_deg, vis, ans;
vector<ll> danger_level;

int n, m;
void init(){
	ans.clear();
	adj.clear();
	vis.clear();
	in_deg.clear();
	out_deg.clear();
	danger_level.clear();
	parents.clear();
	
	
	adj.resize(n);
	parents.resize(n);
	vis.resize(n, 0);
	in_deg.resize(n, 0);
	out_deg.resize(n, 0);
	danger_level.resize(n, 0);
}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	int T; scanf("%d", &T);
	while(T--){
		scanf("%d %d", &n, &m);
		init();
		loop(e, m){
			int a, b; scanf("%d %d", &a, &b);
			a--, b--;
			adj[a].pb(b);
			parents[b].pb(a);
			out_deg[a]++;
			in_deg[b]++;
		}
		set<pair<ll, int>> S;
		loop(i, n) {
			danger_level[i] = in_deg[i] + out_deg[i];
			for(int j : adj[i]) danger_level[i] += out_deg[j];
			for(int p : parents[i]) danger_level[i] += in_deg[p];
//			cerr << i << " " << danger_level[i] << endl;
			S.emplace(danger_level[i], i);
		}
		while(!S.empty()){
			auto [d, u] = *S.rbegin();
			S.erase(*S.rbegin());
			vis[u] = 1;
			if(in_deg[i]+out_deg[i] <= 1) continue; 
			ans.pb(u);
			for(int v : adj[u]) if(!vis[v]){
				S.erase(mp(danger_level[v], v));
				in_deg[v]--;
				danger_level[v] -= 1 + out_deg[v];
				S.emplace(danger_level[v], v);
				for(int c : adj[v]) if(!vis[c]){
					S.erase(mp(danger_level[c], c));
					danger_level[c]--;
					S.emplace(danger_level[c] = in_deg[v]*(ll)out_deg[v], v);					
				}
			}
			for(int v : parents[u]) if(!vis[v]){
				S.erase(mp(danger_level[v], v));
				out_deg[v]--;
				S.emplace(danger_level[v] = in_deg[v]*(ll)out_deg[v], v);
			}
		}
		printf("%d\n", sz(ans));
		for(int u : ans) printf("%d ", u + 1);
		puts("");
	}
	return 0;
}
