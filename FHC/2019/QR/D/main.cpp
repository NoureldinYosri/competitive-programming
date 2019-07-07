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

const int MAXR = 122,MAXN = 66;
int X[MAXR],Y[MAXR],Z[MAXR],n,m;
int par[MAXN],vis[MAXN],H[MAXN];
vi G[MAXN],iG[MAXN],ord;
int inDeg[MAXN];

inline void addEdge(int f,int t) {
	if(f == t) return;
	G[f].push_back(t);
	iG[t].push_back(f);
	inDeg[t]++;
}

bool dfs(int u) {
	if(vis[u]) return vis[u] == 2;
	vis[u] = 1;
	for(int v : G[u])
		if(!dfs(v))
			return 0;
	vis[u] = 2;
	ord.push_back(u);
	return 1;
}


int lca(int x,int y,int *par,int *depth) {
	int a = x,b = y;
	while(a != b) {
		if(depth[a] > depth[b]) a = par[a];
		else b = par[b];
	}
//	cerr << "lca(" << x << ", " << y << ") = " << a << endl;
	return a;
}

void floodFill(int u,int p,int *depth,vi *T) {
	depth[u] = depth[p] + 1;
	for(int v : T[u])
		floodFill(v,u,depth,T);
}

bool validate(){
	static vi T[MAXN];
	static int depth[MAXN];
	for(int u = 1;u <= n;u++) T[u].clear();
	int root = -1;
	for(int u = 1;u <= n;u++){
		if(par[u] == 0){
			assert(root == -1);
			root = u;
		}
		else {
			T[par[u]].push_back(u);
		}
	}
	assert(root != -1);
	floodFill(root,0,depth,T);
	loop(e,m) {
		if(Z[e] != lca(X[e],Y[e],par,depth))
			return 0;
	}
	return 1;
}

bool solve(){
	static queue<int> q;
	for(int i = 1;i <= n;i++) {
		G[i].clear();
		iG[i].clear();
		inDeg[i] = 0;
	}
	loop(r,m) addEdge(Z[r],X[r]),addEdge(Z[r],Y[r]);

	ord.clear();
	for(int i = 1;i <= n;i++)
		vis[i] = 0;
	for(int i = 1;i <= n;i++)
		if(!vis[i])
			if(!dfs(i))
				return 0;

	reverse(all(ord));
	assert(sz(ord) == n);
	loop(i,n) H[ord[i]] = i;
//	prArr(H+1,n,int);
	for(int u = 1;u <= n;u++) {
		par[u] = -1;
		vis[u] = 0;
		if(!inDeg[u]) q.push(u);
	}
	vi aux;
	for(;!q.empty();q.pop()){
		int u = q.front();

		aux.clear();
		for(int p : iG[u]) {
			int gp = p;
			do{
				aux.push_back(gp);
				gp = par[gp];
			}while(gp != -1);
		}
		sort(all(aux));
		aux.resize(unique(all(aux)) - aux.begin());
		sort(all(aux),[](const int & a,const int & b){
			return H[a] > H[b];
		});

		if(!aux.empty()) par[u] = aux[0];
		for(int i = 0;i+1 < sz(aux);i++)
			par[aux[i]] = aux[i + 1];



		for(int v : G[u]) {
			inDeg[v]--;
			if(!inDeg[v])
				q.push(v);
		}
	}
	int root = -1;
	for(int u = 1;u <= n;u++)
		if(par[u] == -1)
			root = u;
	assert(root != -1);
	par[root] = 0;
	for(int u = 1;u <= n;u++)
		if(par[u] == -1)
			par[u] = root;
//	for(int u = 1;u <= n;u++)
//		if(par[u])
//			cerr << par[u] << " " << u << endl;
	return validate();
}



int main(int argc,char **argv){
#ifdef HOME
//	freopen("in.in","r",stdin);
	freopen("data.txt","r",stdin);
	freopen("out.out","w",stdout);
#endif
	int T; scanf("%d",&T);
	for(int t = 1;t <= T;t++) {
		scanf("%d %d",&n,&m);
		loop(r,m) scanf("%d %d %d",X + r,Y + r,Z + r);
//		loop(r,m){
//			if(X[r] != Z[r]) cerr << Z[r] << " " << X[r] << endl;
//			if(Y[r] != Z[r]) cerr << Z[r] << " " << Y[r] << endl;
//		}

		printf("Case #%d: ",t);
		if(solve()) {
			for(int i = 1;i <= n;i++)
				printf("%d%c",par[i]," \n"[i==n]);
		}
		else puts("Impossible");
	}
	return 0;
}
