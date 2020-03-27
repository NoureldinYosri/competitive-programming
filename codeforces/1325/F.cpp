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
#define White 0
#define Black 1
#define Grey 2


int n, m;
vi G[1 << 20];
int cnt[1 << 20];
int visColor[1 << 20];
vi cycle;
int depth[1 << 20], par[1 << 20];
int B;
vi iS;
int deg[1 << 20];


bool dfs(int u){
	visColor[u] = Grey;
	for(int v : G[u]){
		if(visColor[v] == Grey) {
			if (depth[u] - depth[v] + 1 >= B){
				cycle.pb(v);
				cycle.pb(u);
				return 1;
			}
			cnt[u]++;
		}
		else if(visColor[v] == Black) continue;
		else {
			par[v] = u;
			depth[v] = depth[u] + 1;
			if(dfs(v)){
				if(sz(cycle) > 1 && cycle[0] == cycle.back()) return 1;
				cycle.pb(u);
				return 1;
			}
		}
	}
	visColor[u] = Black;
	return 0;
}

bool dead[1 << 20];




int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	scanf("%d %d", &n, &m);
	loop(e, m){
		int a, b; scanf("%d %d", &a, &b);
		G[a].pb(b);
		G[b].pb(a);
	}
	B = sqrt(n) + 5;
	while(B*B > n) B--;
	B += B*B != n;
	dfs(1);
	if(!cycle.empty())
		cycle.pop_back();
	if(sz(cycle) >= B){
		puts("2");
		printf("%d\n", sz(cycle));
		for(int x : cycle) printf("%d ", x);
		puts("");
		return 0;
	}
	

	
	set<pi> SS;
	for(int i = 1;i <= n;i++){
		deg[i] = sz(G[i]);
		SS.emplace(deg[i], i);
	}
	
	while(!SS.empty()){
		auto p = *SS.begin();
		SS.erase(SS.begin());
		
		int u = p.second;
		iS.pb(u);
		dead[u] = 1;
		
		for(int v : G[u]) {
			if(dead[v]) continue;
			dead[v] = 1;
			SS.erase(pi(deg[v], v));
			for(int t : G[v]){
				if(dead[t]) continue;
				SS.erase(pi(deg[t], t));
				deg[t]--;
				SS.emplace(deg[t], t);
			}
		}
	}

	assert(sz(iS) >= B);
	while(sz(iS) > B) iS.pop_back();
	
	puts("1");
	for(int x: iS) printf("%d ", x);
	puts("");
	
	return 0;
}
