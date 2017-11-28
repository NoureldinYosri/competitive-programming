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

const int MAX = 100*1000 + 10;
vi E[MAX],Q[MAX];
int fr[MAX],to[MAX],W[MAX];
int dont[MAX],siz[MAX],mx[MAX],toAdd[MAX],n,m,cnt,tcnt;
ll vals[MAX],target[MAX];
int ans[MAX];
vi record;
int BIT[MAX];


inline void add(int p,int v){
	for(;p <= n;p += LSOne(p))
		BIT[p] += v;
}

inline int get(int p) {
	int res = 0;
	for(;p;p ^= LSOne(p))
		res += BIT[p];
	return res;
}

int dfs(int u,int p) {
	siz[u] = 1;
	mx[u] = 0;
	for(int e : E[u]) {
		int v = fr[e] + to[e] - u;
		if(dont[v] || p == v) continue;
		siz[u] += dfs(v,u);
		mx[u] = max(mx[u],siz[v]);
	}
	return siz[u];
}


void getCenter(int u,int p,int fromParent,int & c) {
	mx[u] = max(mx[u],fromParent);
	if(mx[u] < mx[c]) c = u;
	for(int e : E[u]) {
		int v = fr[e] + to[e] - u;
		if(dont[v] || p == v) continue;
		getCenter(v,u,siz[u] + fromParent - siz[v],c);
	}
}


void prepare(int u,int p,ll len) {
	vals[cnt++] = len;
	for(int e : E[u]) {
		int v = fr[e] + to[e] - u;
		if(dont[v] || p == v) continue;
		prepare(v,u,len + W[e]);
	}
}


void passe(int u,int p,ll len,bool doQ = 0) {
	if(doQ && !Q[u].empty()){
		for(int q : Q[u])
			ans[q] += get(upper_bound(vals,vals + cnt,target[q] - len) - vals);
	}

	toAdd[tcnt++] = upper_bound(vals,vals + cnt,len) - vals;

	for(int e : E[u]) {
		int v = fr[e] + to[e] - u;
		if(dont[v] || p == v) continue;
		passe(v,u,len + W[e],doQ);
	}
}

void divideConquer(int u){
	int siz = dfs(u,0);
	getCenter(u,0,0,u);

	cnt = 0;
	prepare(u,0,0);
	assert(cnt == siz);

	sort(vals,vals + siz);
	cnt = unique(vals,vals + siz) - vals;

	add(1,1);
	record.pb(1);

	for(int e : E[u]) {
		int v = fr[e] + to[e] - u;
		if(dont[v]) continue;
		tcnt = 0;
		passe(v,u,W[e]);
		for(int i = 0;i < tcnt;i++){
			add(toAdd[i],1);
			record.pb(toAdd[i]);
		}
	}

	for(int e : E[u]) {
		int v = fr[e] + to[e] - u;
		if(dont[v]) continue;
		tcnt = 0;
		passe(v,u,W[e]);
		for(int i = 0;i < tcnt;i++)
			add(toAdd[i],-1);

//		cerr << "before going into " << v << " got " << endl;
//		for(int i = 0;i < cnt;i++)
//			cerr << "(" << vals[i] << " ," << get(i+1) << ")" ;
//		cerr << endl;

		tcnt = 0;
		passe(v,u,W[e],1);
		for(int i = 0;i < tcnt;i++)
			add(toAdd[i],1);
	}


	for(int q : Q[u])
		ans[q] += get(upper_bound(vals,vals + cnt,target[q]) - vals);

//	cerr << "after " << u << " got " << ans[0] << endl;
	for(int p : record)
		 add(p,-1);
	record.clear();


	dont[u] = 1;
	for(int e : E[u]) {
		int v = fr[e] + to[e] - u;
		if(dont[v]) continue;
		divideConquer(v);
	}
}


int main(){
	#ifdef HOME
		freopen("in.in", "r", stdin);
	#endif
	scanf("%d %d",&n,&m);
	loop(e,n-1) {
		scanf("%d %d %d",fr + e,to + e,W + e) ;
		E[fr[e]].pb(e);
		E[to[e]].pb(e);
	}
	loop(i,m) {
		int v;
		scanf("%d %lld",&v,target + i);
		Q[v].pb(i);
	}

	divideConquer(1);

	loop(i,m) printf("%d\n",ans[i]);
	return 0;
}
