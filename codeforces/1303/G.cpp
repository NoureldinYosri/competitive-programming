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
 
const int MAXV = 150000  + 10, MAXE = 2*MAXV;
const ll MAXA = MAXV*(MAXV + 1LL)*1e6 + 10, oo = 1LL << 60;
vi G[MAXV];
bool dead[MAXV];
int siz[MAXV], mx[MAXV];
int A[MAXV], n;
 
 
using line = pair<ll, ll>;
 
struct node{
	node *l, *r;
	line v;
	node (){
		l = r = 0;
		v = line(0, -oo);
	}
};
 
auto f = [](const line & A, const ll & x){
	return A.first * x + A.second;
};
 
void add_line(node *& cur, line nw, ll l = 0, ll r = MAXA) {
	if(!cur){
		cur = new node();
		cur->v = nw;
		return;
	}
	if(l == r){
		if(f(nw, l) > f(cur->v, l)) cur->v = nw;
		return;
	}
    ll m = l + (r-l)/2;
    bool lef = f(nw, l) > f(cur->v, l);
    bool mid = f(nw, m) > f(cur->v, m);
    if(mid) {
        swap(cur->v, nw);
    }
	
	if(lef != mid) {
        add_line(cur->l, nw, l, m);
    } else {
        add_line(cur->r, nw, m+1, r);
    }
}
ll get(node *cur, ll x, ll l = 0, ll r = MAXA) {
	if(!cur) return -oo;
//	cerr << "query " << cur->v << " " << x << endl;
    ll m = l + (r - l)/2;
    ll ret = 0;
    if(l == r) {
        ret = f(cur->v, x);
    } else if(x < m) {
        ret = max(f(cur->v, x), get(cur->l, x, l, m));
    } else {
        ret = max(f(cur->v, x), get(cur->r, x, m+1, r));
    }
    assert(ret >= 0);
    return ret;
}
 
int floodfill(int u, int p){
	siz[u] = 1;
	mx[u] = 0;
	for(int v : G[u]) if(v != p && !dead[v]){
		floodfill(v, u);
		siz[u] += siz[v];
		mx[u] = max(mx[u], siz[v]);
	}
	return siz[u];
}
 
int get_center(int u, int p, int s){
	mx[u] = max(mx[u], s - siz[u]);
	int c = u;
	for(int v : G[u]) if(v != p && !dead[v]){
		int g = get_center(v, u, s);
		if(mx[g] < mx[c]) c = g;
	}
	return c;
}
 
ll query(int u, int p, ll w_sum_up, ll sum_up, int len_up, ll w_sum_down, ll sum_down, int len_down, node *up, node *down){
	len_down++;
	sum_down += A[u];
	w_sum_down += A[u] * (ll)len_down;
	
	len_up++;
	sum_up += A[u];
	w_sum_up += sum_up;
	
//	cerr << "@" << u << " up " << w_sum_up << " " << sum_up << " down " << w_sum_down << " " << sum_down << endl;
	ll ret = max(get(up, sum_down) + w_sum_down, get(down, len_up) + w_sum_up);
//	cerr << "@" << u << " " << ret << endl;
	
	assert(ret >= max(w_sum_down, w_sum_up));
	
	for(int v : G[u]) if(v != p && !dead[v])
		ret = max(ret, query(v, u, w_sum_up, sum_up, len_up, w_sum_down, sum_down, len_down, up, down));
	
//	cerr << "@" << u << " " << ret << endl;	
	return ret;
}
 
void insert(int u, int p, ll w_sum_up, ll sum_up, int len_up, ll w_sum_down, ll sum_down, int len_down, node *& up, node *& down){
	len_down++;
	sum_down += A[u];
	w_sum_down += A[u] * (ll)len_down;
	
	len_up++;
	sum_up += A[u];
	w_sum_up += sum_up;
	
	//cerr << "insert up " << line(len_up, w_sum_up) << endl;
	//cerr << "insert down " << line(sum_down, w_sum_down) << endl;
	add_line(up, line(len_up, w_sum_up));
	add_line(down, line(sum_down, w_sum_down));
	
	for(int v : G[u]) if(v != p && !dead[v])
		insert(v, u, w_sum_up, sum_up, len_up, w_sum_down, sum_down, len_down, up, down);	
}
ll DC(int u){
	u = get_center(u, 0, floodfill(u, 0));
	
	//cerr << "root is " << u << endl;
	
	ll ret = A[u];
	node *up = 0, *down = 0;
	add_line(up, line(1, A[u]));
	add_line(down, line(0, 0));
	
	for(int v : G[u]) if(!dead[v]){
		ret = max(ret, query(v, u, A[u], A[u], 1, 0, 0, 0, up, down));
		insert(v, u, A[u], A[u], 1, 0, 0, 0, up, down);
	}
	
	dead[u] = 1;
	for(int v : G[u]) if(!dead[v]){
		ret = max(ret, DC(v));
	}
	
	return ret;
}
 
 
int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	scanf("%d", &n);
	loop(e, n-1){
		int a, b; scanf("%d %d", &a, &b);
		G[a].pb(b);
		G[b].pb(a);
	}
	for(int i = 1; i <= n; i++)
		scanf("%d", A + i);
	
	printf("%lld\n", DC(1));
	return 0;
}
