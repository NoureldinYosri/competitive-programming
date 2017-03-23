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

int vis[101][101][101];
int n;
vp G[101];

void bfs(int c,int s){
	queue<int> q;
	vis[c][s][s] = 1; q.push(s);
	while(!q.empty()){
		int u = q.front(); q.pop();
		for(auto e : G[u]) if(e.yy == c && !vis[c][s][e.xx]) q.push(e.xx),vis[c][s][e.xx] = 1;
	}
}	

int main(){
	int m; scanf("%d %d",&n,&m);
	loop(i,m){
		int a,b,c;
		scanf("%d %d %d",&a,&b,&c);
		G[a].pb(mp(b,c));
		G[b].pb(mp(a,c));
	}	
	range(c,1,m) range(s,1,n) bfs(c,s);
	int q; scanf("%d",&q);
	while(q--){
		int u,v; scanf("%d %d",&u,&v);
		int ans = 0;
		range(c,1,m) ans += vis[c][u][v];
		printf("%d\n",ans);
	}
	
	return 0;
}
