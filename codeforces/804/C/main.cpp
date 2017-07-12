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

const int MAX = 300*1000 + 10;

set<int> S[MAX];
vi T[MAX],G[MAX],rG[MAX];
int n,m;
int color[MAX];

void dfs(int u,int p){
	int cur = 1;
	sort(all(rG[u]));
	set<int> used;
	for(int c : rG[u])
		if(color[c])
			used.insert(color[c]);
	for(int c : rG[u])
		if(!color[c]){
			while(used.find(cur) != used.end()) cur++;
			color[c] = cur++;
		}
	for(int v : T[u]) if(v != p) dfs(v,u);
}

int main(){
	#ifndef ONLINE_JUDGE
		freopen("in.in", "r", stdin);
	#endif
	scanf("%d %d",&n,&m);
	range(u,1,n){
		int k ; scanf("%d",&k);
		range(i,1,k){
			int x; scanf("%d",&x);
			G[x].pb(u);
			rG[u].pb(x);
		}
	}
	loop(i,n-1){
		int a,b; scanf("%d %d",&a,&b);
		T[a].pb(b);
		T[b].pb(a);
	}
	dfs(1,0);
	range(i,1,m) if(!color[i]) color[i] = 1;
	int ans = 0;
	range(i,1,m) ans = max(ans,color[i]);
	printf("%d\n",ans);
	range(i,1,m) printf("%d%c",color[i]," \n"[i==m]);
	return 0;
}
