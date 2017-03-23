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

int dist[3000][3000];
vi G[3000];
int n,m,s1,s2,t1,t2,l1,l2;
int oo = 1 << 28;

void bfs(int s,int *dist){
	fill(dist,dist + n,oo);
	queue<int> q; q.push(s); dist[s] = 0;
	while(!q.empty()){
		int u = q.front(); q.pop();
		for(int v : G[u]) if(dist[v] == oo){
			dist[v] = dist[u] + 1;
			q.push(v);
		}
	}
}	

int main(){
	scanf("%d %d",&n,&m);
	loop(i,m){
		int a,b; scanf("%d %d",&a,&b); a--,b--;
		G[a].pb(b);
		G[b].pb(a);
	}
	scanf("%d %d %d",&s1,&t1,&l1); s1--,t1--;
	scanf("%d %d %d",&s2,&t2,&l2); s2--,t2--;
	loop(i,n) bfs(i,dist[i]);
	
	int ans = -1;	
	loop(i,n) loop(j,n) {
		int d1 = dist[s1][i] + dist[i][j] + dist[j][t1];
		int d2 = dist[s2][i] + dist[i][j] + dist[j][t2];
		int l = d1 + d2 - dist[i][j];
		if(d1 <= l1 && d2 <= l2 && l <= m) ans = max(ans,m - l); //,cerr << i << " " << j << " " << l << endl;
		d2 = dist[s2][j] + dist[i][j] + dist[i][t2];
		l = d1 + d2 - dist[i][j];
		if(d1 <= l1 && d2 <= l2 && l <= m) ans = max(ans,m - l); //,cerr << i << " " << j << " " << l << endl;
	}
	if(dist[s1][t1] <= l1 && dist[s2][t2] <= l2 && dist[s1][t1] + dist[s2][t2] <= m)
		ans = max(ans,m - dist[s1][t1] - dist[s2][t2]);
	cerr << ans << endl;
	cout << ans << endl;
	return 0;
}
