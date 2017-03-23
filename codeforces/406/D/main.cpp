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

const int MAX = 1e5 + 1e2;
ll X[MAX],H[MAX];
int higher[MAX],lower[MAX],nxt[MAX],n;
vi G[MAX];
int ord[MAX << 1],ST[MAX << 1][20],lg[MAX << 1],lst[MAX],depth[MAX],dfs_time;
int deg[MAX];

ll ccw(int i,int j,int k){
	ll ux = X[j] - X[i],uy = H[j] - H[i];
	ll vx = X[k] - X[i],vy = H[k] - H[i];
	return ux * vy - uy * vx;
}

bool valid(int i,int j,int k){
	return ccw(j,i,k) < 0;
}

void dfs(int u){
	ord[dfs_time] = u;
	lst[u] = dfs_time++;
	for(int v : G[u]) if(v != u) {
		depth[v] = depth[u] + 1;		
		dfs(v);
		ord[dfs_time] = u;
		lst[u] = dfs_time++;
	}
}

int argmin(int a,int b){
	return (depth[a] < depth[b]) ? a : b;
}

void buildST(){
	lg[0] = -1;
	loop(i,dfs_time) lg[i + 1] = lg[i] + ((i + 1) == LSOne(i + 1));
	loop(i,dfs_time) ST[i][0] = ord[i];
	loop(k,19) loop(i,dfs_time){
		int j = i + (1 << k);
		if(j >= dfs_time) j = i;
		ST[i][k + 1] = argmin(ST[i][k],ST[j][k]);
	}
}

int main(){
	scanf("%d",&n);
	loop(i,n) scanf("%lld %lld",X + i,H + i);
	nxt[n - 1] = n - 1;
	for(int i = n-2;i >= 0;i--){
		nxt[i] = i + 1;
		while(nxt[nxt[i]] != nxt[i] && valid(i,nxt[i],nxt[nxt[i]]))
			nxt[i] = nxt[nxt[i]];
		G[nxt[i]].pb(i);
	}
	loop(i,n) for(int v : G[i]) {
		deg[v] ++;
//		cerr << i+1 << " " << v+1 << endl;
	}
	int zero = 0;
	loop(i,n) zero += deg[i] == 0;
	assert(zero == 1);
	

	dfs(n-1);
	assert(dfs_time == 2*n - 1);
	buildST();

	int m ; scanf("%d",&m);
	loop(i,m){
		int a,b; scanf("%d %d",&a,&b); a--,b--;
		a = lst[a],b = lst[b];
		if(a > b) swap(a,b);
		int l = lg[b - a + 1];
		printf("%d%c",argmin(::ST[a][l],::ST[b - (1 << l) + 1][l]) + 1," \n"[i==m-1]);
	}		
	return 0;
}
