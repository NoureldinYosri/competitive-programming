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

const int MAX = 1 << 20;
int C[MAX][2],n;
vi G[MAX];
int color[MAX];

bool dfs(int u,int c){
	if(color[u]) return color[u] == c;
	color[u] = c;
	for(int v : G[u]) if(!dfs(v,3-c)) return 0;
	return 1;
}

int main(){
	scanf("%d",&n);
	loop(i,n) {
		loop(j,2) scanf("%d",&C[i][j]),C[i][j]--;
		G[C[i][0]].pb(C[i][1]);	
		G[C[i][1]].pb(C[i][0]);
	}
	range(i,1,n) {
		int a = i << 1,b = a - 1;
		G[a].pb(b);
		G[b].pb(a);
	}
	range(i,1,2*n) if(!color[i]) {
		if(!dfs(i,1)) {
			puts("-1");
			return 0;
		}
	}
	loop(i,n) printf("%d %d\n",color[C[i][0]],color[C[i][1]]);
	return 0;
}
