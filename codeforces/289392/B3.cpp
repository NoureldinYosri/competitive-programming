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


vi id, W, ans;
vector<map<int, int>> info;
vi lst, nxt, BIT;
vector<vp> queries;
int n, m, k;

pi find(int a){
	if(id[a] == a) return pi(a, INT_MAX);
	auto [p, t] = find(id[a]);
	t = min(t, info[id[a]][a]);
	return pi(p, t);
}
void join(int a, int b, int e){
	int t1, t2;
	tie(a, t1) = find(a);
	tie(b, t2) = find(b);
	if(a == b) return;
	if(W[a] < W[b]) swap(a, b);
	W[a] += W[b];
	id[b] = a;
	info[a][b] = min({t1, t2, e});
}
bool areConnected(int a, int b){
	return find(a).first == find(b).first;
}
int getTime(int a, int b){
	int ret = INT_MAX;
	while(a != b){
		assert(a && b);
		if(W[a] < W[b]) swap(a, b);
//		cerr << b << " -> " << id[b] << " @" << info[id[b]][b] << endl;
		ret = min(ret, info[id[b]][b]);
		b = id[b];
	}
	return ret;
}

void add(int p, int v){
	for(; p < sz(BIT); p += LSOne(p))
		BIT[p] += v;
}
int get(int p){
	int ret = 0;
	for(; p; p ^= LSOne(p))
		ret += BIT[p];
	return ret;
}


int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	scanf("%d %d", &n, &m);
	BIT.resize(m + 1, 0);
	id.resize(n+1);
	W.resize(n+1);
	info.resize(n+1);
	lst.resize(m+1, -1);
	nxt.resize(m+1, -1);
	queries.resize(m+1);
	fill(all(W), 1);
	iota(all(id), 0);
	
	for(int e = 1; e <= m; e++){
		int a, b; scanf("%d %d", &a, &b);
		if(areConnected(a, b)){
			int z = getTime(a, b);
//			cerr << a << " " << b << " -> " << z << endl;
			nxt[lst[z]] = e;
			lst[z] = e;
		} else {
			join(a, b, e);
			add(e, 1);
			lst[e] = e;
		}
	}
	
	scanf("%d", &k);
	ans.resize(k, 0);
	
	loop(t, k){
		int l, r; scanf("%d %d", &l, &r);
		queries[l].emplace_back(r, t);
	}

	for(int l = 1; l <= m; l++){
//		cerr << "@" << l << endl;
		for(auto [r, q] : queries[l]){
//			cerr << r << " " << q << " " << sz(BIT) << endl;
			ans[q] = get(r) - get(l-1);
		}
		add(l, -1);
//		cerr << "erase " << l << endl;
		if(nxt[l] != -1) {
			add(nxt[l], 1);
//			cerr << "isert " << nxt[l] << endl;
		}
	}
	
	for(int v : ans) printf("%d\n", n - v);
	return 0;
}
