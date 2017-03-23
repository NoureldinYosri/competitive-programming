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

vp G[401];
vi E[401];
int dist[401],to[401];

int main(){
	freopen("defence.in","r",stdin);
	freopen("defence.out","w",stdout);
	int n,m,s,t; scanf("%d %d %d %d",&n,&m,&s,&t);
	range(i,1,m){
		int a,b; scanf("%d %d",&a,&b);
		G[a].pb(mp(b,i));
		G[b].pb(mp(a,i));	
	}	
	memset(dist,-1,sizeof dist);
	queue<int> q;	
	q.push(s); dist[s] = 0;	
	while(!q.empty()){
		int u = q.front(); q.pop();
		for(auto e : G[u]){
			int v = e.xx;
			if(dist[v] == -1){
				dist[v] = dist[u] + 1;
				q.push(v);
			}
		}
	}
	range(u,1,n)
		for(auto e : G[u]){
			int v = e.xx;
			if(dist[v] == dist[u] + 1)
				E[dist[v]].pb(e.yy);				
		}
	printf("%d\n",dist[t]);
	range(i,1,dist[t]) {
		printf("%d",sz(E[i]));
		for(int e : E[i]) 
			printf(" %d",e);
		puts("");
	}	
	
	return 0;
}
