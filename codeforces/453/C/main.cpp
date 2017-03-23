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

const int MAX = 100'000 + 10;
vi G[MAX],path;
int vis[MAX],n,X[MAX],Y[MAX],m;


void dfs(int u,int isRoot = 0){
	vis[u] = 1;
	path.pb(u);
	Y[u] = 1;
	for(int v : G[u]){
		if(!vis[v]){
			dfs(v);
			path.pb(u);
			Y[u] ^= 1;
			if(Y[v] != X[v]){
				path.pb(v);
				path.pb(u);
				Y[v] ^= 1;
				Y[u] ^= 1;
			}
		}		
	}
	if(isRoot && Y[u] != X[u]) path.pop_back(),Y[u] ^= 1;
}

int main(){
	scanf("%d %d",&n,&m);
	loop(i,m){
		int a,b; scanf("%d %d",&a,&b);
		G[a].pb(b);
		G[b].pb(a);
	}
	range(i,1,n) scanf("%d",X + i);
	range(i,1,n) if(X[i]) {
		dfs(i,1);
		break;
	}
	//print(path,int);
	range(i,1,n) if(X[i] != Y[i]){
		puts("-1");
		return 0;
	}
	assert(sz(path) <= 4*n);
	printf("%d\n",sz(path));
	for(int u : path) printf("%d ",u);	
	
	return 0;
}
