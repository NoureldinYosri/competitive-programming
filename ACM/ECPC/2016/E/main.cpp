#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define range(i,a,b) for(int i = (a);i <= (b);i++)
#define all(A) A.begin(),A.end()
#define pb push_back
#define mp make_pair
#define sz(A) ((int)A.size())
#define vi vector<int>
#define vl vector<long long>
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
const double PI = acos(-1);
using namespace std;

const int MAX = 100000 + 10;
int D[MAX],n;
int dist[MAX];
vi G[MAX];


void bfs(int root) {
	memset(dist,-1,sizeof dist);
	queue<int> q;
	q.push(root); dist[n] = 0;

	while(!q.empty()){
		int u = q.front() ; q.pop();
		for(int v : G[u])
			if(dist[v] == -1) {
				dist[v] = dist[u] + 1;
				q.push(v);
			}
	}


}

void solve(){
	scanf("%d",&n);
	range(i,1,n) {
		scanf("%d",D + i);
		G[i].clear();
	}
	range(i,1,n) {
		if(i + D[i] <= n) G[i + D[i]].pb(i);
		if(i - D[i] >= 1) G[i - D[i]].pb(i);
	}
	bfs(n);
}

int main(){
	freopen("jumping.in", "r", stdin);
	int T; scanf("%d",&T);
	while(T--) {
		solve();
		range(i,1,n) printf("%d\n",dist[i]);
	}
	return 0;
}
