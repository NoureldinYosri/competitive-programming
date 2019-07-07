#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define range(i,a,b) for(int i = (a);i <= (b);i++)
#define all(A) A.begin(),A.end()
#define pb push_back
#define mp make_pair
#define sz(A) ((int)A.size())
#define vi vector<int>
#define vd vector<double>
#define vp vector<pair<int,int> >
#define ll long long
#define pi pair<int,int>
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
using namespace std;

const int MAXN = 100*1000 + 10;
vi G[MAXN],C[MAXN],done[MAXN];
int siz[MAXN],biggestChild[MAXN];
int ST[MAXN],EN[MAXN],D[MAXN],F[MAXN],K[MAXN];
int BIT[MAXN],n;
bool dont[MAXN];

inline void update(int p,int v) {
	for(++p;p < MAXN;p += LSOne(p))
		BIT[p] += v;
}
inline int get(int p) {
	int ret = 0;
	for(++p;p > 0; p ^= LSOne(p))
		ret += BIT[p];
	return ret;
}

void dfs(int u,int p) {
	siz[u] = 1;
	biggestChild[u] = 0;
	for(int v : G[u]) {
		if(v == p || dont[v]) continue;
		dfs(v,u);
		siz[u] += siz[v];
		biggestChild[u] = max(biggestChild[u],siz[v]);
	}
}

int getCenter(int u,int p,int s) {
	int c = u;
	biggestChild[u] = max(biggestChild[u],s - siz[u]);
	for(int v : G[u]){
		if(v == p || dont[v]) continue;
		int t = getCenter(v,u,s);
		if(biggestChild[t] < biggestChild[c])
			c = t;
	}
	return c;
}

void dfs(int u,int p,int d,int s) {
	update(d,s);
	for(int v : G[u]) {
		if(v == p || dont[v]) continue;
		dfs(v,u,d+1,s);
	}
}

void work(int u,int p,int d) {
	F[u] += get(D[u] - d);
	for(int v : G[u])
		if(!dont[v] && v != p)
			work(v,u,d+1);
}

int DC(int u,bool f) {
	if(f){
		dfs(u,0);
		int s = siz[u];
		u = getCenter(u,0,s);
	}

	update(0,1);
	for(int v : G[u]) {
		if(dont[v]) continue;
		dfs(v,u,1,1);
	}

	F[u] += get(D[u]);
	for(int v : G[u]) {
		if(dont[v]) continue;
		dfs(v,u,1,-1);
		work(v,u,1);
		dfs(v,u,1,1);
	}

	update(0,-1);
	for(int v : G[u]){
		if(dont[v]) continue;
		dfs(v,u,1,-1);
	}
	dont[u] = 1;
	if(f){
		for(int v : G[u])
			if(!dont[v])
				C[u].pb(DC(v,1));
	}
	else{
		for(int c : C[u])
			DC(c,0);
	}
	return u;
}

bool itr(bool f,int & root) {
	for(int i = 1;i <= n;i++){
		D[i] = ST[i] + (EN[i] - ST[i] + 1)/2;
		F[i] = 0;
		dont[i] = 0;
	}
	root = DC(root,f);
	for(int i = 1;i <= n;i++)
		F[i] = n - F[i];
//	prArr(D+1,n,int);
//	prArr(F+1,n,int);
//	prArr(K+1,n,int);
	for(int i = 1;i <= n;i++){
		if(F[i] >= K[i]) ST[i] = D[i];
		else EN[i] = D[i] - 1;
	}
	for(int i = 1;i <= n;i++)
		D[i] = ST[i];
	for(int i = 1;i <= n;i++)
		if(ST[i] != EN[i])
			return 1;
	return 0;
}

int main(int argc,char **argv){
#ifdef HOME
	freopen("in.in","r",stdin);
#endif
	scanf("%d",&n);
	for(int i = 1;i <= n;i++) scanf("%d",K + i);
	loop(i,n-1) {
		int a,b; scanf("%d %d",&a,&b);
		G[a].pb(b);
		G[b].pb(a);
	}
	for(int i = 1;i <= n;i++) {
		ST[i] = 0;
		EN[i] = n;
	}
	int root = 1;
	for(int i = 0;i < 20 && itr(i==0,root);i++);
	for(int i = 1;i <= n;i++)
		printf("%d%c",D[i]," \n"[i==n]);
	return 0;
}
