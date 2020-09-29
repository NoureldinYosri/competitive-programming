#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define all(A) A.begin(),A.end()
#define pb push_back
#define mp make_pair
#define sz(A) ((int)A.size())
typedef std::vector<int> vi;
typedef std::pair<int,int> pi;
typedef std::vector<pi> vp;
typedef long long ll;
#define popcnt(x) __builtin_popcount(x)
#define LSOne(x) ((x) & (-(x)))
#define print(A,t) cerr << #A << ": "; copy(all(A),ostream_iterator<t>(cerr," " )); cerr << endl
#define prArr(A,n,t)  cerr << #A << ": "; copy(A,A + n,ostream_iterator<t>(cerr," " )); cerr << endl
#define PRESTDIO() cin.tie(0),cerr.tie(0),ios_base::sync_with_stdio(0)
#define what_is(x) cerr << #x << " is " << x << endl
#define bit_lg(x) (assert(x > 0),__builtin_ffsll(x) - 1)
const double PI = acos(-1);
template<class A,class B>
std::ostream& operator << (std::ostream& st,const std::pair<A,B> p) {
	st << "(" << p.first << ", " << p.second << ")";
	return st;
}
using namespace std;


const int MAXN = 100*1000 + 10, MAXST = 1 << 20, mod = 1e9 + 7;

int add(int a, int b){
	a += b;
	if(a >= mod) a -= mod;
	if(a < 0) a += mod;
	return a;
}
int mul(int a, int b ){
	return (a*(ll)b)%mod;
}
int powmod(int a, int p){
	if(!p) return 1;
	int b = 1;
	for(; p > 1; p >>= 1){
		if(p&1) b = mul(a, b);
		a = mul(a, a);
	}
	return mul(a, b);
}
int inv(int a){
	return powmod(a, mod-2);
}

int ST[MAXST], LA[MAXST];
int A[MAXN], n;
vi G[MAXN];
int dfs_in[MAXN], dfs_out[MAXN], euler[MAXN], dfs_time;

void dfs(int u, int p, int prod){
	euler[dfs_time] = prod;
	dfs_in[u] = dfs_time++;
	prod = mul(prod, A[u]);
	for(int v : G[u]) if(v != p) dfs(v, u, prod);
	dfs_out[u] = dfs_time;
}

void build(int cur, int s, int e){
	LA[cur] = 1;
	if(s == e){
		ST[cur] = euler[s];
		return ;
	}
	int m = (s + e) >> 1, left = 2*cur + 1, right = left + 1;
	build(left, s, m);
	build(right, m+1, e);
	ST[cur] = add(ST[left], ST[right]);
}

void update(int cur, int v){
	ST[cur] = mul(ST[cur], v);
	LA[cur] = mul(LA[cur], v);
}

void push_down(int cur){
	if(LA[cur] == 1) return;
	int left = 2*cur + 1, right = left + 1;
	update(left, LA[cur]);
	update(right, LA[cur]);
	LA[cur] = 1;
}

void update(int cur, int s, int e, int l, int r, int v){
	if(l <= s && e <= r) return update(cur, v);
	push_down(cur);
	int m = (s + e) >> 1, left = 2*cur + 1, right = left + 1;
	if(r <= m) update(left, s, m, l, r, v);
	else if(m < l) update(right, m+1, e, l, r, v);
	else {
		update(left, s, m, l, m, v);
		update(right, m+1, e, m+1, r, v);
	}
	ST[cur] = add(ST[left], ST[right]);
	assert(LA[cur] == 1);
}

int query(int cur, int s, int e, int l, int r){
	if(l <= s && e <= r) return ST[cur];
	push_down(cur);
	int m = (s + e) >> 1, left = 2*cur + 1, right = left + 1;
	if(r <= m) return query(left, s, m, l, r);
	else if(m < l) return query(right, m+1, e, l, r);
	else return add(query(left, s, m, l, m), query(right, m+1, e, m+1, r));
}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	int m; scanf("%d %d", &n, &m);
	loop(e, n-1){
		int a, b; scanf("%d %d", &a, &b);
		G[a].pb(b);
		G[b].pb(a);
	}
	for(int u = 1; u <= n; u++) scanf("%d", A + u);
	dfs(1, 0, 1);
	build(0, 0, n-1);
	
	while(m--){
		int t; scanf("%d", &t);
		if(t == 1){
			int u, x; scanf("%d %d", &u, &x);
			int scaler = mul(x, inv(A[u]));
			A[u] = x;
			int l = dfs_in[u] + 1, r = dfs_out[u] - 1;
			//cerr << l << " " << r << " " << scaler << endl;
			if(l <= r)
				update(0, 0, n-1, l, r, scaler);
		}
		else {
			int u; scanf("%d", &u);
			printf("%d\n", query(0, 0, n-1, dfs_in[u], dfs_out[u]-1));
		}
	}
	
	return 0;
}
