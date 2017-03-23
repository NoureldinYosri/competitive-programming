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

int C[501][501];
vi G[501];
int X[501];

int main(){
	int n,m; scanf("%d %d",&n,&m);
	range(i,1,n) scanf("%d",X + i);
	fill(&C[0][0],&C[501][0],-(1 << 28));
	loop(i,m){
		int a,b,c; scanf("%d %d %d",&a,&b,&c);
		C[a][b] = C[b][a] = c;
		G[a].pb(b);
		G[b].pb(a);
	}	
	ll x = 0,y = 1;
	range(u,1,n) for(int v : G[u]) {
		if((X[u] + X[v])*y > x*C[u][v])
			x = X[u] + X[v],y = C[u][v];
	}
	
	cerr << x*1.0/y << endl;
	range(u,1,n) for(int v : G[u]) for(int t : G[v]) if(t != u) {
		if((C[u][v] + C[v][t] + C[u][t]) > 0 && (X[u] + X[v] + X[t])*y > x*(C[u][v] + C[v][t] + C[u][t]))
			x = X[u] + X[v] + X[t],y = C[u][v] + C[v][t] + C[u][t];
	}
	printf("%.15f\n",x*1.0/y);
	cerr << x*1.0/y << endl;
	return 0;
}
