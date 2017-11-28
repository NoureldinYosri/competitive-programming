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

struct operat {
	int x,y,yt;
};
const int MAX = 200*1000 + 10;
int dont[MAX];
vector<operat> ans;
vi G[MAX];
int siz[MAX],mx[MAX],parent[MAX];

int n;

void dfs(int u,int p){
	siz[u] = 1;
	mx[u] = 0;
	parent[u] = p;
	for(int v : G[u]) if(v != p && !dont[v]) {
		dfs(v,u);
		siz[u] += siz[v];
		mx[u] = max(mx[u],siz[v]);
	}
}

void get_center(int u,int p,int total_siz,int & c){
	mx[u] = max(mx[u],total_siz - siz[u]);
	if(mx[u] < mx[c]) c = u;
	for(int v : G[u]) if(v != p && !dont[v]) get_center(v,u,total_siz,c);
}

pi DC(int u,int p,bool can_cut = 1){
	dfs(u,p);
	int total_siz = siz[u];
	if(total_siz == 1) return mp(u,1);
	int center = u;
	get_center(u,p,total_siz,center);

	//cerr << "@" << u << " center is " << center << endl;

	vi sons (sz(G[center]),0);
	loop(i,sz(G[center])) {
		int v = G[center][i];
		if(v != p && !dont[v] && parent[v] == center) sons[i] = 1;
	}
	int sum = 1;
	for(int v : G[center]) if(v != p && !dont[v] && parent[v] == center) sum += siz[v];
	dont[center] = 1;
	loop(i,sz(G[center])) {
		int v = G[center][i];
		if(v != p && !dont[v]) {
			int cur_siz = 0;
			if(parent[v] == center) cur_siz = siz[v];
			else cur_siz = total_siz - sum;
			pi tmp = DC(v,center,(n - cur_siz) > cur_siz);
			int t = tmp.xx;
			if(can_cut){
				if(v != t) ans.pb(operat({center,v,t}));
			}
			else if(sons[i]){
				if(u != center) ans.pb(operat({v,center,u}));
			}
		}
	}
	return mp(center,total_siz);
}


int main(){
	#ifdef HOME
		freopen("in.in", "r", stdin);
	#endif
	scanf("%d",&n);
	loop(i,n-1){
		int a,b;
		scanf("%d %d",&a,&b);
		G[a].pb(b);
		G[b].pb(a);
	}
	DC(1,0);
	printf("%d\n",sz(ans));
	for(auto e : ans)
		printf("%d %d %d\n",e.x,e.y,e.yt);
	#ifdef DEBUG
	  eprintf("Time %.2f\n", (double) clock() / CLOCKS_PER_SEC);
	#endif
	return 0;
}
