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

const int mod = 998244353 ;
int add(int a, int b){
	a += b;
	if(a >= mod) a -= mod;
	return a;
}
int mul(int a, int b){
	return (a*(ll)b)%mod;
}
int powmod(int a, int p){
	if(!p) return 1;
	int b = 1;
	for(; p > 1; p >>= 1){
		if(p & 1) b = mul(a, b);
		a = mul(a, a);
	}
	return mul(a, b);
}
int inv(int a){
	return powmod(a, mod-2);
}

const int MAXN = 300*1000 + 10;
struct quanta{
	int color, count;
	bool isNotEmpty;
	quanta(){
		color = count = 0;
		isNotEmpty = false;
	}
	quanta(int co, int cn){
		color = co;
		count = cn;
		isNotEmpty = false;
	}
	friend ostream& operator << (ostream & st, const quanta & q) {
		st << "{color: " << q.color << ", count: " << q.count << ", isEmpty: " << !q.isNotEmpty << "}";
		return st;
	}
};

int n, m;
vi E[MAXN];
int fr[MAXN], to[MAXN];
int color[MAXN];
int cnt[MAXN];
bool isGood[MAXN];

quanta dfs(int u, int p){
	vector<quanta> aux;
	bool isNotEmpty = false;	
	for(int e : E[u]) {
		int v = fr[e] + to[e] - u;
		if(v == p) continue;
		quanta tmp = dfs(v, u);
		if(tmp.color && tmp.count < cnt[tmp.color]){
			aux.pb(tmp);
		} else {

		}
		if(tmp.isNotEmpty && (tmp.color==0 || tmp.count == cnt[tmp.color])) {
			isGood[e] = true;
//			cerr << "\tis good " << u << " " << v << endl;
		} else{
//			cerr << "\tnot good " << u << " " << v << endl; 
		}
		isNotEmpty |= tmp.isNotEmpty;
	}
	sort(all(aux), [](const quanta & a, const quanta & b){
		return a.color < b.color;
	});
	vector<quanta> res;
	for(int i = 0; i < sz(aux); ){
		int j = i;
		int ctr = 0;
		while(j < sz(aux) && aux[i].color == aux[j].color) {
			ctr += aux[j].count;
			j++;
		}
		res.pb(quanta(aux[i].color, ctr));
		i = j;
	}
	if(sz(res) > 1) {
//		cerr << "multiway at " << u << endl;
		puts("0");
		exit(0);
	}
	if(color[u]){
		if(res.empty()){
			res.pb(quanta(color[u], 1));
		} else if(res[0].color != color[u]){
//			cerr << "cloging at " << u << endl;
			puts("0");
			exit(0);
		} else {
			res[0].count++;
		}
		isNotEmpty = true;
	} else if(!res.empty()){
		color[u] = -1;
	}
	quanta ret = res.empty() ? quanta() : res[0];
	ret.isNotEmpty = isNotEmpty;
//	cerr << u << " " << ret << endl;
	return ret;
}

bool vis[1 << 20];

pi solve(int u, int p){
	if(color[u]) return pi(1, 0);
	if(vis[u]) return pi(1, 0);
	vis[u] = true;
	int f = 1;
	vi aux;
	for(int e : E[u]) if(isGood[e]) {
		int v = fr[e] + to[e] - u;
		if(v == p) continue;
		auto [fv, lv] = solve(v, u);
		lv++;
		f = mul(f, fv);
		aux.pb(lv);
	}
	if(aux.empty()){
		assert(p == 0);
		return pi(1, 0);
	}
	int s = 0;
	if(sz(aux) == 1) s = aux[0];
	else {
		int tmp = 1, ways = 0;
		for(int x : aux) tmp = mul(tmp, x + 1);
		for(int x: aux) ways = add(ways, mul(tmp, inv(x + 1)));
		f = mul(f, ways);
		s = 0;
	}
	cerr << pi(p, u) << ": " << pi(f, s) << endl;
	return pi(f, s);
}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	scanf("%d %d", &n, &m);
	for(int u = 1; u <= n; u++) {
		scanf("%d", color + u);
		cnt[color[u]]++;
	}
	loop(e, n-1){
		scanf("%d %d", fr + e, to + e);
		E[fr[e]].pb(e);
		E[to[e]].pb(e);
//		cerr << fr[e] << "-" << color[fr[e]] << " " << to[e] << "-" << color[to[e]] << endl;
	}
	int root = 1;
	while(!color[root]) root++;
	dfs(root, 0);
/*	cerr << endl;
	loop(e, n-1) if(isGood[e]){
		cerr << fr[e] << "-" << color[fr[e]] << " " << to[e] << "-" << color[to[e]] << endl;
	}
*/	
	int ans = 1;
	for(int u = 1; u <= n; u++)
		if(color[u] == 0 && !vis[u]){
			auto [f, s] = solve(u, 0);
			if(s) f = mul(f, s);
			ans = mul(ans, f);
		}
	cout << ans << endl;
	return 0;
}
