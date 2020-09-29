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


int n, m;
vi A, BIT, Y, ans;
vector<vp> queries;

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

const int oo = 1 << 29;

int ST[1 << 20], CNT[1 << 20];

void build(int cur, int s, int e){
	ST[cur] = oo;
	if(s == e) return;
	int m = (s + e) >> 1, left = 2*cur + 1, right = left + 1;
	build(left, s, m);
	build(right, m+1, e);
}

void spawn(int cur, int s, int e, int p, int v){
	if(s == e){
		ST[cur] = v;
		//doesn't affect ST[cur][1]
		return;
	}
	int m = (s + e) >> 1, left = 2*cur + 1, right = left + 1;
	if(p <= m) spawn(left, s, m, p, v);
	else spawn(right, m+1, e, p, v);
	ST[cur] = min(ST[left], ST[right] - CNT[left]);
}

int dfs(int cur, int s, int e, int h){
	if(ST[cur] > h) {
//		cerr << "return from " << pi(s, e) << " because " << ST[cur] << " > " << h << endl;
		return CNT[cur];
	}
	if(s == e){
//		cerr << pi(s, A[s]) << " is now good" << endl;
		add(s, 1);
		ST[cur] = oo;
		return CNT[cur] = 1;
	}
	int m = (s + e) >> 1, left = 2*cur + 1, right = left + 1;
	h += dfs(left, s, m, h);
	h += dfs(right, m+1, e, h);
	ST[cur] = min(ST[left], ST[right] - CNT[left]);
	return CNT[cur] = CNT[left] + CNT[right];
}


int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	scanf("%d %d", &n, &m);
	A.resize(n+1);
	queries.resize(n+1);
	BIT.resize(n+1);
	ans.resize(m);
	for(int i = 1; i <= n; i++) {
		scanf("%d", &A[i]);
	}
	loop(q, m){
		int x, y; scanf("%d %d", &x, &y);
		queries[x].emplace_back(q, y);
	}
	build(0, 1, n);
	A[0] = oo;
	for(int e = n; e >= 0; e--){
		dfs(0, 1, n, 0);
		for(auto [q, y] : queries[e])
			ans[q] = get(n - y);
			
		if(A[e] <= e){
		//	cerr << "spawn " << pi(e, A[e]) << endl;
			spawn(0, 1, n, e, e - A[e]);
		}
	}
	for(int v : ans) printf("%d\n", v);
	return 0;
}
