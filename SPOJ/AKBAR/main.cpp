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

const int MAX = 1e6+1e2;
vi G[MAX];
int vis[MAX];
int N,R,M;

bool bfs(int u,int p,int id){
	if(vis[u]) return 0;
	queue<int> q;
	q.push(u);
	vis[u] = id;
	while(!q.empty() && p > 0){
		for(int i = 0,L = q.size();i < L;i++){
			u = q.front(); q.pop();
			for(int v : G[u]){
				if(vis[v]){
					if(vis[v] != id) {
					//	cerr << v << " failed" << endl;						
						return 0;
					}
				}
				else {
					vis[v] = id;
					q.push(v);
				}
			}
		}
		p--;
	}
	return 1;
}

bool solve(){
	scanf("%d %d %d",&N,&R,&M);
	fill(vis+1,vis+N+1,0);
	range(i,1,N) G[i].clear();
	loop(i,R){
		int a,b; scanf("%d %d",&a,&b);
		G[a].pb(b);
		G[b].pb(a);		
	}
	loop(i,M){
		int city,power; scanf("%d %d",&city,&power);
		if(!bfs(city,power,i+1)) return 0;
	}
//	prArr(vis+1,N,int);
	range(i,1,N) if(!vis[i]) return 0;
	return 1;
}

int main(){
	int T; scanf("%d",&T);
	while(T--) puts(solve() ? "Yes" : "No");	
	
	
	return 0;
}
