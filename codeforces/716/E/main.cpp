#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define range(i,a,b) for(int i = (a);i <= (b);i++)
#define all(A) A.begin(),A.end()
#define PI acos(-1)
#define pb push_back
#define mp make_pair
#define sz(A) ((int)A.size())
#define vi vector<int>
#define vl vector<long long>
#define vd vector<double>
#define vp vector<pair<int,int> >
#define ll long long
#define pi pair<int,int>
#define point pair<double,double>
#define pl pair<ll,ll>
#define popcnt(x) __builtin_popcount(x)
#define LSOne(x) ((x) & (-(x)))
#define xx first
#define yy second
#define PQ priority_queue
#define print(A,t) cerr << #A << ": "; copy(all(A),ostream_iterator<t>(cerr," " )); cerr << endl
#define prp(p) cerr << "(" << (p).first << " ," << (p).second << ")";
#define prArr(A,n,t)  cerr << #A << ": "; copy(A,A + n,ostream_iterator<t>(cerr," " )); cerr << endl
#define PRESTDIO() cin.tie(0),cerr.tie(0),ios_base::sync_with_stdio(0)
using namespace std;

const int MAX = 100010;
int mod,n,m,k;
vi E[MAX];
int fr[MAX],to[MAX],digit[MAX];
int p10[MAX],inv[MAX];
ll ans = 0;
int visID[MAX],visid = 1;
int mxsiz[MAX],siz[MAX];
bool dont[MAX];
map<int,int> out[MAX];

int mul(int x,int y){
	x %= mod;
	y %= mod;
	return (x*1LL*y)%mod;
}

int pow_mod(int x,int y){
	if(!y) return 1;
	int z = 1;
	for(;y > 1;y >>= 1){
		if(y & 1) z = mul(x,z);
		x = mul(x,x);
	}
	return mul(x,z);
}

int get_phi(){
	int m = mod;
	int ret = m;
	for(int i = 2;i*i <= m;i++)
		if(m%i == 0){
			ret -= ret/i;
			while(m%i == 0) m /= i;
		}
	if(m != 1) ret -= ret/m;
	return ret;
}

int dfs_cnt(int u,int p){
	siz[u] = 1;
	mxsiz[u] = 0;
	for(int e : E[u]) {
		int v = fr[e] + to[e] - u;
		if(v == p || dont[v]) continue;
		int t = dfs_cnt(v,u);
		mxsiz[u] = max(mxsiz[u],t);
		siz[u] += t;
	}
	return siz[u];
}

void get_root(int u,int p,int & root,int V){
	mxsiz[u] = max(mxsiz[u],V - siz[u]);
	if(root == -1 || mxsiz[u] < mxsiz[root]) root = u;
	for(int e : E[u]) {
		int v = fr[e] + to[e] - u;
		if(v == p || dont[v]) continue;
		get_root(v,u,root,V);
	}
}


void precompute(int u,int p,ll cost,int depth,map<int,int> & save){
	save[cost %= mod]++;
	for(int e : E[u]) {
		int v = fr[e] + to[e] - u;
		if(v == p || dont[v]) continue;
		precompute(v,u,digit[e]*1LL*p10[depth] + cost,depth + 1,save);
	}
}

void solve(int u,int p,ll cost,int depth,map<int,int> & U,map<int,int> & V){
	cost %= mod;
	int target = mul(inv[depth],mod - cost);
	if(U.find(target) != U.end()) ans += U[target];
	if(V.find(target) != V.end()) ans -= V[target];
	for(int e : E[u]) {
		int v = fr[e] + to[e] - u;
		if(v == p || dont[v]) continue;
		solve(v,u,cost*10 + digit[e],depth + 1,U,V);
	}
}

void divide_conquer(int u,int p){
//	cerr << "D&C " << u << " " << p << endl;
	int V = dfs_cnt(u,p),root = -1;
	get_root(u,p,root,V);
	if(root == -1) return;

	u = root;
	out[u].clear();
	out[u][0]++;

//	cerr << "root = " << root << endl;
	dont[p] = 1;
	for(int e : E[root]) {
		int v = fr[e] + to[e] - root;
		if(v == p || dont[v]) continue;
		out[v].clear();
		precompute(v,root,digit[e],1,out[v]);
//		cerr << v << " : " ;
		for(auto p : out[v]) {
			out[u][p.xx] += p.yy;
//			prp(p);
		}
//		cerr << endl;
	}
	ans += out[u][0] - 1;
/*	cerr << "res : ";
	for(auto p : out[u]) prp(p);
	cerr << endl;
*/	for(int e : E[root]) {
		int v = fr[e] + to[e] - u;
		if(v == p || dont[v]) continue;
		solve(v,u,digit[e],1,out[u],out[v]);
	}
	for(int e : E[root]) {
		int v = fr[e] + to[e] - u;
		if(v == p || dont[v]) continue;
		divide_conquer(v,u);
	}
}


int main(){
	#ifndef ONLINE_JUDGE
		freopen("in.in", "r", stdin);
	#endif
	scanf("%d %d",&n,&mod);
	if(mod == 1){
		cout << n*(n - 1LL) << endl;
		return 0;
	}
	loop(e,	n-1){
		scanf("%d %d %d",fr + e,to + e,digit + e);
		fr[e]++,to[e]++;
		E[fr[e]].pb(e);
		E[to[e]].pb(e);
//		cerr << fr[e] << " " << to[e] << " " << digit[e] << endl;
	}
	int phi = get_phi();

	p10[0] = 1;
	loop(i,n+5) p10[i+1] = mul(p10[i],10);
	loop(i,n+6) inv[i] = pow_mod(p10[i],phi - 1);

	divide_conquer(1,0);
	cout << ans << endl;
	return 0;
}
