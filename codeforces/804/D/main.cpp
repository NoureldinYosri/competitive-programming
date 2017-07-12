#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define range(i,a,b) for(int i = (a);i <= (b);i++)
#define all(A) A.begin(),A.end()
#define pb push_back
#define mp make_pair
#define sz(A) ((int)A.size())
#define vi vector<int>
#define vl vector<long long>
#define vd vector<double>
#define vp vector<pair<int,int> >
#define ll long long
#define pi pair<int,int>
#define pl pair<ll,ll>
#define popcnt(x) __builtin_popcountll(x)
#define LSOne(x) ((x) & (-(x)))
#define xx first
#define yy second
#define PQ priority_queue
#define print(A,t) cerr << #A << ": "; copy(all(A),ostream_iterator<t>(cerr," " )); cerr << endl
#define prp(p) cerr << "(" << (p).first << " ," << (p).second << ")";
#define prArr(A,n,t)  cerr << #A << ": "; copy(A,A + n,ostream_iterator<t>(cerr," " )); cerr << endl
#define PRESTDIO() cin.tie(0),cerr.tie(0),ios_base::sync_with_stdio(0)
#define what_is(x) cerr << #x << " is " << x << endl
#define bit_lg(x) (assert(x > 0),__builtin_ffsll(x) - 1)
const double PI = acos(-1);
using namespace std;

const int MAX = 100*1000 + 10;
vi G[MAX];
int id[MAX],is_tree[MAX];
int n,m,N;
vi H[MAX];
ll S[MAX];
vi len[MAX];
vl pref[MAX];
int diameter[MAX];

bool dfs(int u,int p,int idx){
	id[u] = idx;
	int r = 1;
	for(int v : G[u]) if(v != p) {
		if(id[v]) r = 0;
		else if(!dfs(v,u,idx)) r = 0;
	}
	return r;
}

int dfs(int u,int p){
	int mx = 0;
	for(int v : G[u]) {
		if(v != p){
			H[u].pb(dfs(v,u) + 1);
			mx = max(mx,H[u].back());
		}
		else H[u].pb(0);
	}
	return mx;
}

void dfs(int u,int p,int fr_parent,ll & sum,int & diameter,vi & len){
	loop(i,sz(H[u])) if(G[u][i] == p) H[u][i] = fr_parent;
	int mx = fr_parent;
	for(int h : H[u]) mx = max(mx,h);
	sum += mx;
	len.pb(mx);
	vi V(sz(H[u]));
	mx = 0;
	for(int i = sz(H[u]) - 1;i >= 0;i--){
		V[i] = mx;
		mx = max(mx,H[u][i]);
	}
	mx = 0;
	for(int i = 0;i < sz(G[u]);i++) {
		if(G[u][i] != p) {
			int in = max(mx,V[i]) + 1;
			dfs(G[u][i],u,in,sum,diameter,len);
		}
		mx = max(mx,H[u][i]);
	}
	sort(all(H[u]));
	reverse(all(H[u]));
	if(H[u].size() > 1) diameter = max(diameter,H[u][0] + H[u][1]);
	else if(H[u].size()) diameter = max(diameter,H[u][0]);
}

map<pi,double> dp;

double solve(int u,int v){
	if(mp(sz(len[u]),u) > mp(sz(len[v]),v)) swap(u,v);
	if(dp.find(mp(u,v)) != dp.end()) return dp[mp(u,v)];
/*	cerr << u << " " << diameter[u] << endl;
	print(len[u],int);
	print(pref[u],ll);
	cerr << v << " " << diameter[v] << endl;
	print(len[v],int);
	print(pref[v],ll);
*/
	int d = max(diameter[u],diameter[v]);
	ll ret = 0;
	for(int h : len[u]){
		auto p = lower_bound(all(len[v]),d - h - 1) - len[v].begin();
		ll tmp = 0;
		if(!p)	tmp += pref[v].back() + (h + 1LL) * sz(pref[v]);
		else{
			tmp += (pref[v].back() - pref[v][p - 1]) + (h + 1LL) * (sz(pref[v]) - p);
			tmp += p *1LL* d;
		}
		ret += tmp;
	}
	dp[mp(u,v)] = ret/(sz(len[u]) * 1.0 * sz(len[v]));
	return dp[mp(u,v)];
}

int main(){
	#ifndef ONLINE_JUDGE
		freopen("in.in", "r", stdin);
	#endif
	int q; scanf("%d %d %d",&n,&m,&q);
	loop(i,m){
		int a,b; scanf("%d %d",&a,&b);
		G[a].pb(b);
		G[b].pb(a);
	}
	range(u,1,n) if(!id[u]) {
		++N;
		is_tree[N] = dfs(u,0,N);
		if(is_tree[N]) {
			dfs(u,0);
			dfs(u,0,0,S[N],diameter[N],len[N]);
			sort(all(len[N]));
			ll sum = 0;
			for(int x : len[N]) {
				sum += x;
				pref[N].pb(sum);
			}
		}
	}

	while(q--){
		int u,v; scanf("%d %d",&u,&v);
		u = id[u],v = id[v];
		if(u == v || !is_tree[u] || !is_tree[v]) puts("-1");
		else printf("%.20f\n",solve(u,v));
	}
	return 0;
}
