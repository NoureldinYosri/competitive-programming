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


const int MAXN = 200*1000 + 10;
vi G[MAXN];
int ID[MAXN], dfs_num[MAXN], dfs_low[MAXN], dfs_time;
bool vis[MAXN], is_articulation[MAXN];
int color[MAXN], n, m;

void dfs(int u, int p){
	dfs_num[u] = dfs_low[u] = dfs_time++;
	vis[u] = 1;
	int child_cnt = 0;
	for(int v : G[u]) {
		if(!vis[v]){
			child_cnt++;
			dfs(v, u);
			if(dfs_low[v] >= dfs_num[u]) is_articulation[u] = 1;
			dfs_low[u] = min(dfs_low[u], dfs_low[v]);
		}
		else if(v != p) dfs_low[u] = min(dfs_low[u], dfs_num[v]);
	}
	if(p == 0) is_articulation[u] = child_cnt > 1;
}

void read(){
	int m; scanf("%d %d", &n ,&m);
	for(int i = 1; i <= n; i++) scanf("%d", color + i);
	loop(e, m){
		int a, b; scanf("%d %d", &a, &b);
		G[a].pb(b);
		G[b].pb(a);
	}
}

void Bi(){
	for(int i = 1; i <= n;i++) if(!vis[i]) dfs(i, 0);
//	prArr(is_articulation + 1, n, bool);
}

vi ST;
vector<vi> blocks;


void poll(int root){
//	cerr << "poll up to " << root << endl;
	static vi aux;
	bool any = 0;
	aux.clear();
	while(!ST.empty() && ST.back() != root){
		aux.pb(ST.back());
		ID[ST.back()] = m;
		ST.pop_back();
		any = 1;
	}
	if(root != -1) aux.pb(root);
	if(any){
		sort(all(aux));
		aux.resize(unique(all(aux)) - aux.begin());
		if(sz(aux) == 1 && is_articulation[aux[0]]) return;  
//		print(aux, int);
		blocks.emplace_back(aux);
	}
}

void dfs2(int u, int p){
	if(is_articulation[u]) ID[u] = m++;
	vis[u] = 1;
	ST.pb(u);
	for(int v : G[u]) if(!vis[v]){
		dfs2(v, u);
		if(dfs_low[v] >= dfs_num[u] && is_articulation[u]) {
//			cerr << "poll from " << u << " " << p << endl;
			poll(u);
		}
		else ST.pb(u);
	}
}


vector<vi> F;

void compress(){
	memset(vis, 0, sizeof vis);
	for(int i = 1; i <= n;i++) if(!vis[i]) {
		dfs2(i, 0);
		poll(-1);
	}
	for(int i = 1; i <= n; i++) if(is_articulation[i]) {
		ID[i] = sz(blocks);
		blocks.emplace_back();
		blocks.back().pb(i);
	}
	m = sz(blocks);
	F.resize(m);
/*	loop(i, m){
		cerr << i << ":";
		for(int x : blocks[i]) if(!is_articulation[x] || (is_articulation[x] && sz(blocks[i]) == 1)) cerr << " " << x;
		cerr << endl;
	}
*/	loop(i, sz(blocks))
		for(int u : blocks[i]) if(is_articulation[u] && i != ID[u]){
			F[i].pb(ID[u]);
//			cerr << i << " " << ID[u] << endl;
			F[ID[u]].pb(i);
		}
}


vector<map<int, int>> cnt;
int connectedID[2*MAXN];
int tot[1 << 20];
int siz[2*MAXN], pref_child[2*MAXN];

void floodfill(int u, int p){
//	cerr << "visit " << u << " from " << p << endl;
	vis[u] = 1;
	connectedID[u] = sz(cnt) - 1;
	pref_child[u] = -1;
	siz[u] = 0;
//	print(blocks[u], int);
	for(int x : blocks[u]) {
		if(!is_articulation[x] || (is_articulation[x] && sz(blocks[u]) == 1)){
			cnt.back()[color[x]]++;
			siz[u]++;
//			cerr << "append " << x << " with color " << color[x] << endl;
		}
	}
	for(int v : F[u]) if(v != p) {
		floodfill(v, u);
		siz[u] += siz[v];
		if(pref_child[u] == -1 || siz[v] > siz[pref_child[u]])
			pref_child[u] = v;
	}
}

ll ans[MAXN];


pair<ll, map<int, int>*> dfs(int u, int p, map<int, int> & have){
	vis[u] = 1;
	ll ret = 0;
	map<int, int> *M = 0;
	if(pref_child[u] != -1) tie(ret, M) = dfs(pref_child[u], u, have);
	else M = new map<int, int>();
	
	ll cost = ret;
	
	for(int v : F[u]) if(v != p && v != pref_child[u]) {
		ll _;
		map<int, int> *subtree;
		tie(_, subtree) = dfs(v, u, have);
		for(auto p : *subtree){
			int x, c;
			tie(x, c) = p;
			int b = M->count(x) ? M->at(x) : 0;
			int a = have[x] - b - c;
			
			cost += a*(ll)c;
			
			ret -= b*(ll)c;
			ret += a*(ll)c;
			
			(*M)[x] = b + c;	
		}
	}
	for(int y : blocks[u]) if(!is_articulation[y] || (is_articulation[y] && sz(blocks[u]) == 1)){
		int x = color[y], c = 1;
		int b = M->count(x) ? M->at(x) : 0;
		int a = have[x] - b - c;
		//cerr << "at " << u << " x " << x << " | " << a << " " << b << " " << c << endl;
		
		cost += a*(ll)c;
		
		ret -= b*(ll)c;
		ret += a*(ll)c;
		
		(*M)[x] = b + c;	
		ans[y] += have[x] - 1;		
	}
	
	if(sz(blocks[u]) == 1){
		int y = blocks[u].back();
		int x = color[y];
		ans[y] += cost - (have[x] - 1);
	}
/*	cerr << u << ": " << ret << " ";
	for(auto p : *M) cerr << p;
	cerr << endl;
*/	return mp(ret, M);
}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	read();
	Bi();
	compress();
	memset(vis, 0, sizeof vis);
	ll ctr0 = 0;
	loop(i, m) if(!vis[i]) {
		cnt.emplace_back();
		floodfill(i, -1);
		for(auto p : cnt.back()){
			int c, s;
			tie(c, s) = p;
//			cerr << c << " " << s << endl;
			ctr0 += s*tot[c];
			tot[c] += s;
		}
//		cerr << endl;
	}
//	cerr << "ctr0 " << ctr0 << endl;
	for(int i = 1; i <= n; i++) ans[i] = ctr0;
//	prArr(ans+1, n, ll);
	
	memset(vis, 0, sizeof vis);
	int j = 0;
	loop(i, m) if(!vis[i]){
		dfs(i, -1, cnt[j]);
		j++;
	}
//	prArr(ans+1, n, ll);
	for(int i = 1; i <= n; i++) printf("%lld%c", ans[i], " \n"[i==n]);
	return 0;
}
