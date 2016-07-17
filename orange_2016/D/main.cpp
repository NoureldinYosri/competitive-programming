#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define range(i,a,b) for(int i = (a);i <= (b);i++)
#define rrep(i,n) for(int i = (n);i >= 0;i--)
#define rran(i,a,b) for(int i = (b);i >= (a);i--)
#define all(A) A.begin(),A.end()
#define PI acos(-1)
#define pb push_back
#define mp make_pair
#define sz(A) A.size()
#define vi vector<int>
#define vl vector<long>
#define vd vector<double>
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

int V[1024][1024],n,m;
vi G[1024];


void bfs(int s){
	V[s][s] = 1;
	queue<int> q;
	q.push(s);
	while(!q.empty()){
		int u = q.front(); q.pop();
		for(int v : G[u]){
			if(V[s][v]) continue;
			V[s][v] = 1;
			q.push(v);
		}
	}
}

int main(){
	scanf("%d %d",&n,&m);
	loop(i,m){
		int a,b;
		scanf("%d %d",&a,&b);
		G[a].pb(b);
	}
	loop(i,n) bfs(i + 1);
	scanf("%d",&m);
	loop(i,m){
		int a,b;
		scanf("%d %d",&a,&b);
		puts(V[a][b] ? "YES" : "NO");
	}	
	return 0;
}
