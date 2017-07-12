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
#define pl pair<ll,ll>
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

int S,T;
vp G[1 << 20];
int vis[1 << 20],n,m;

bool bfs(int msk){
	memset(vis,0,sizeof vis);
	queue<int> q;
	q.push(S); vis[S] = 1;
	while(!q.empty()){
		int u = q.front(); q.pop();
		for(auto e : G[u]){
			int v = e.xx,c = e.yy;
			if((c & msk) != c) continue;
			if(vis[v]) continue;
			vis[v] = 1;
			q.push(v);
		}
	}
	return vis[T];
}

int main(){
	#ifndef ONLINE_JUDGE
		freopen("in.in", "r", stdin);
		freopen("out.out", "w", stdout);
	#endif
	scanf("%d %d",&n,&m);
	scanf("%d %d",&S,&T);
	while(m--){
		int a,b,c; scanf("%d %d %d",&a,&b,&c);
		G[a].pb(mp(b,c));
		G[b].pb(mp(a,c));
	}
	int ans = INT_MAX;
	for(int i = 30;i >= 0;i--){
		if(bfs(ans ^ (1 << i)))
			ans ^= 1 << i;
	}
	cout << ans << endl;
	cerr << ans << endl;
	return 0;
}
