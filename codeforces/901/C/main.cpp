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

const int MAXN = 300*1000 + 10,MAXE = 2*MAXN;
int articulation_vertex[MAXN],dfs_low[MAXN],dfs_num[MAXN],dfs_time;
int bridge[MAXN],n,m;
int head[MAXN],to[MAXE],nxt[MAXE],edge_cnt;
vi ST,U[MAXE];
int compCnt;
int mn[MAXE],mx[MAXE],S[MAXN],E[MAXN];
ll pref[MAXN];

void init(){
	memset(head,-1,sizeof head);
	memset(dfs_num,-1,sizeof dfs_num);
}

void addEdge(int f,int t){
	int e = edge_cnt++;
	to[e] = t;
	nxt[e] = head[f];
	head[f] = e;
}

void addBiEdge(int f,int t) {
	addEdge(f,t);
	addEdge(t,f);
}

void extract(int upToAndIncluding) {
	bool done = 0;
	do{
//		cerr << ST.back() << " ";
		U[compCnt].pb(ST.back());
		done = ST.back() == upToAndIncluding;
		ST.pop_back();
	}while(!done);
//	cerr << endl;
//	cerr << "=================" << endl;
	compCnt++;
}

void dfsBi(int u,int pe,int dfs_root) {
	dfs_low[u] = dfs_num[u] = dfs_time++;
	ST.push_back(u);
	int t = 0;
	for(int e = head[u];~e;e = nxt[e]){
		int v = to[e];
		if (dfs_num[v] == -1) {
			if (u == dfs_root) t++;
			dfsBi(v,e,dfs_root);
			if (dfs_low[v] > dfs_num[u]){
//				cerr << u << " " << v << " is bridge" << endl;
				bridge[e] = 1;
				extract(v);
			}
			if (u != dfs_root && dfs_low[v] >= dfs_num[u]){
//				cerr << u << " is articulation point" << endl;
				articulation_vertex[u] = 1;
				extract(u);
				ST.push_back(u);
			}
			if(ST.back() != u) ST.push_back(u);
			dfs_low[u] = min(dfs_low[u], dfs_low[v]);
		}
		else if (pe==-1 || e != (pe^1))
			dfs_low[u] = min(dfs_low[u], dfs_num[v]);
	}
//	cerr << u << " " << sz(ST) << " " << dfs_root << endl;
//	print(ST,int);
	if(u == dfs_root && t > 1) {
		articulation_vertex[u] = 1;
		ST.pop_back();
		while(!ST.empty())
			extract(u);
	}
	if(u == dfs_root && !ST.empty()){
		ST.pop_back();
		if(!ST.empty()) extract(u);
	}
	if(u == dfs_root) assert(ST.empty());
}

ll getSum(int l,int r){
	return r*(r+1LL)/2 - l*(l-1LL)/2;
}
ll getPref(int r,int p,int R) {
	if(r < p) return pref[r] - getSum(0,r) + r + 1;
	return getPref(p-1,p,R) + R*(r-p+1LL) - getSum(p,r) + (r-p+1);
}


int main(){
	#ifdef HOME
		freopen("in.in", "r", stdin);
	#endif
	init();
	scanf("%d %d",&n,&m);
	loop(i,m){
		int a,b; scanf("%d %d",&a,&b);
		addBiEdge(a,b);
	}

	range(u,1,n) if(dfs_num[u] == -1) dfsBi(u,-1,u);
	fill(mn,mn + compCnt,INT_MAX);

	loop(i,compCnt)  {
		sort(all(U[i]));
		U[i].resize(unique(all(U[i])) - U[i].begin());
		if(sz(U[i]) <= 1 || sz(U[i])%2 == 0) continue;
//		print(U[i],int);
		int l = U[i][0],r = U[i].back();
		S[r] = max(S[r],l);
	}
//	prArr(S,n+1,int);
	for(int i = 1,j = 1;i <= n;i++) {
		j = max(i,j);
		while(j+1 <= n && S[j+1] < i) j++;
		E[i] = j;
		pref[i] = pref[i - 1] + E[i];
	}
//	prArr(E,n+1,int);

	assert(is_sorted(E,E + n + 1));
	int Q; scanf("%d",&Q);
	while(Q--) {
		int l,r; scanf("%d %d",&l,&r);
		int p = upper_bound(E,E + n + 1,r) - E;
		ll ans = getPref(r,p,r) - getPref(l-1,p,r);
		printf("%lld\n",ans);
	}

	return 0;
}
