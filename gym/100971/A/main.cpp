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
#define popcnt(x) __builtin_popcount(x)
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


const int MAX = 200*1000 + 10;
vi G[MAX];
int C[MAX],D[MAX],n;
int vis[MAX],ord[MAX],indeg[MAX];

int dfs(int u){
	if(vis[u]) return D[u];
	vis[u] = 1;
	for(int v : G[u])
		D[u] = min(D[u],dfs(v) - C[v]);
	return D[u];
}

bool find_cycle(int u){
	if(vis[u]) return vis[u] == 1;
	vis[u] = 1;
	for(int v : G[u]){
		if(find_cycle(v)) return 1;
	}
	vis[u] = 2;
	return 0;
}

int main(){
	//freopen("logger.out","w",stderr);
	#ifndef ONLINE_JUDGE
		freopen("input.in", "r", stdin);
		freopen("output.out", "w", stdout);
	#endif
	scanf("%d",&n);
	range(i,1,n){
		scanf("%d %d",D + i,C + i);
		int m; scanf("%d",&m);
		while(m--){
			int x; scanf("%d",&x);
			G[x].pb(i);
			indeg[i]++;
		}
	}
	vi roots;
	range(i,1,n) if(indeg[i] == 0){
		if(find_cycle(i)) {
			puts("NO");
			return 0;
		}
		roots.pb(i);
	}
	if(roots.empty()){
		puts("NO");
		return 0;
	}
	memset(vis,0,sizeof vis);
	for(int root : roots) dfs(root);
	loop(i,n) ord[i] = i + 1;
	sort(ord,ord + n,[](const int & a,const int & b){
		return D[a] < D[b];
	});
	int t = 0;
	loop(i,n){
		if(t + C[ord[i]] > D[ord[i]]){
			puts("NO");
			return 0;
		}
		t += C[ord[i]];
	}
	puts("YES");
	loop(i,n) printf("%d%c",ord[i]," \n"[i==n-1]);
	return 0;
}
