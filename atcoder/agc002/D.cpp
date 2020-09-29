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

const int MAX = 100*1000 + 10;
vi idx, fr, to;
int n, m;
int id[MAX], W[MAX];
vector<pair<int*, int>> ST;
int stack_size[MAX];

void change(int *x, int v){
	ST.emplace_back(x, *x);
	*x = v;
}

int find(int a){
	if(id[a] == a) return a;
	int v = find(id[a]);
	change(&id[a], v);
	return id[a];
}
bool join(int a, int b){
	a = find(a), b = find(b);
	if(a == b) return 0;
	if(W[a] < W[b]) swap(a, b);
	change(&W[a], W[a] + W[b]);
	change(&id[b], a);
	return 1;
}



void build(int m, bool save = 1){
	static int lst = -1;
	for(int e = lst; e > m; e--){
		while(sz(ST) > stack_size[e]){
			auto [p, v] = ST.back();
			ST.pop_back();
			*p = v;
		}
	}
	for(int e = lst+1; e <= m; e++) {
		stack_size[e] = sz(ST);
		join(fr[e], to[e]);
	}
	lst = m;
}

int X[1 << 20], Y[1 << 20], Z[1 << 20], ans[1 << 20];

int Q[1 << 20];

void dfs(int s, int e, int* l, int* r){
	if(l == r) return;
	if(s == e){
		for(; l != r; l++) ans[*l] = idx[s];
		return;
	}
	int m = (s + e) >> 1;
	build(m);
	auto ptr = partition(l, r, [](const int & q){
		int a = X[q], b = Y[q];
		a = find(a), b = find(b);
		int cnt = W[a] + (a != b)*W[b];
		return cnt >= Z[q];
	});
	
	dfs(s, m, l, ptr);
	dfs(m+1, e, ptr, r);
}
void init(){
	loop(i, n) id[i] = i, W[i] = 1;
}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	scanf("%d %d", &n, &m);
	init();
	loop(e, m){
		int a, b; scanf("%d %d", &a, &b);
		a--, b--;
		if(join(a, b)) {
			idx.pb(e+1);
			fr.pb(a);
			to.pb(b);
		}
	}
	init();
	scanf("%d", &m);
	loop(i, m) {
		scanf("%d %d %d", X + i, Y + i, Z + i);
		X[i]--, Y[i]--;
		Q[i] = i;
	}
	dfs(0, sz(idx)-1, Q, Q + m);
	loop(q, m) printf("%d\n", ans[q]);
	return 0;
}
