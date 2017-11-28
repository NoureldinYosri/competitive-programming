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

const int MAX = 3e5 + 10;
vi E[MAX];
int fr[MAX],to[MAX],done[MAX];
int D[MAX],deg[MAX];
int vis[MAX];
int n,m;
vi reserve[MAX];
vi ans;

void flood_fill(int u){
	vis[u] = 1;
	D[u] = -1;
	for(int e : E[u]) {
		int v = fr[e] + to[e] - u;
		if(vis[v]) continue;
		ans.pb(e);
		done[e] = 1;
		if(!vis[v]) flood_fill(v);
	}
}

int main(){
	#ifdef HOME
		freopen("in.in", "r", stdin);
	#endif
	scanf("%d %d",&n,&m);
	range(i,1,n) scanf("%d",D + i);
	loop(e,m) {
		scanf("%d %d",fr + e,to + e);
		E[fr[e]].pb(e);
		E[to[e]].pb(e);
	}
	range(i,1,n) if(D[i] == -1 && !vis[i]) flood_fill(i);
	queue<int> q;
	range(i,1,n) if(!vis[i]) {
		deg[i] = sz(E[i]);
		if(D[i] == 1 && deg[i] == 1) q.push(i);
	}
	while(!q.empty()){
		int u = q.front(); q.pop();
		vis[u] = 1;
		if(!D[u]) continue;
		if(!deg[u]) {
			puts("-1");
			return 0;
		}
		D[u] ^= 1;
		for(int e : E[u]){
			int v = fr[e] + to[e] - u;
			if(vis[v]) continue;
			D[v] ^= 1;
			deg[v]--;
			ans.pb(e);
			if(D[v] == 1 && deg[v] == 1) q.push(v);
		}
	}
	range(i,1,n) if(D[i] == 1) {
		puts("-1");
		return 0;
	}
	printf("%d\n",sz(ans));
	loop(i,sz(ans)) printf("%d%c",ans[i]+1," \n"[i==sz(ans)-1]);
	return 0;
}
