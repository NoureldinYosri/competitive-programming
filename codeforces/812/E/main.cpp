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

int XOR[2],cnt[2];
vi G[1 << 20];
int P[1 << 20],A[1 << 20],color[1 << 20];
int n;

void dfs(int u,int depth = 0){
	XOR[depth] ^= A[u];
	cnt[depth]++;
	color[u] = depth;
	for(int v : G[u]) dfs(v,depth ^ 1);
}

int main(){
	#ifndef ONLINE_JUDGE
		freopen("in.in", "r", stdin);
	#endif
	scanf("%d",&n);
	range(i,1,n) scanf("%d",A + i);
	range(i,2,n) {
		scanf("%d",P + i);
		G[P[i]].pb(i);
	}
	dfs(1);
	bool cond = 0;
	range(u,1,n) if(G[u].empty()) cond = 1 ^ color[u];
	if(cond) swap(XOR[0],XOR[1]);
	ll ans = 0;
	map<int,int> cnt;
	range(u,1,n) if(!color[u]) cnt[A[u]^XOR[1]]++;
	range(u,1,n) if(color[u] && cnt.find(A[u]) != cnt.end()) ans += cnt[A[u]];
	if(!XOR[1]){
		loop(i,2) ans += cnt[i]*(cnt[i] - 1LL)/2;
	}
	cout << ans << endl;
	return 0;
}
