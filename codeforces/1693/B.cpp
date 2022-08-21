#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define all(A) A.begin(),A.end()
#define pb push_back
#define mp make_pair
#define sz(A) ((int)A.size())
using vi = std::vector<int>;
using pi = std::pair<int,int>;
using vp = std::vector<pi>;
using ll = long long;
#define popcnt(x) __builtin_popcount(x)
#define LSOne(x) ((x) & (-(x)))
#define print(A,t) cerr << #A << ": "; copy(all(A),ostream_iterator<t>(cerr," " )); cerr << endl
#define prArr(A,n,t)  cerr << #A << ": "; copy(A,A + n,ostream_iterator<t>(cerr," " )); cerr << endl
#define PRESTDIO() cin.tie(0),cerr.tie(0),ios_base::sync_with_stdio(0)
#define what_is(x) cerr << #x << " is " << x << endl
#define bit_lg(x) (assert(x > 0),__builtin_ffsll(x) - 1)
template<class A,class B>
std::ostream& operator << (std::ostream& st,const std::pair<A,B> p) {
	st << "(" << p.first << ", " << p.second << ")";
	return st;
}
void tc();
auto test_cases = [](){
	int T; scanf("%d", &T);
	while(T--) tc();
};
using namespace std;

vector<vi> child;
int n;
vp bounds;
vector<ll> val;

int dfs(int u) {
	int ret = 0;
	val[u] = 0;
	for(int v : child[u]) {
		ret += dfs(v);
		val[u] += val[v];
	}
	auto [l, r] = bounds[u];
	if(val[u] > r) {
		val[u] = r;
	}
	if(val[u] < l) {
		ret++;
		val[u] = r;
	}
	return ret;
}

void tc(){
	scanf("%d", &n);
	child.clear();
	child.resize(n);
	bounds.resize(n);
	val.resize(n);
	for(int i = 1; i < n; i++) {
		int p; scanf("%d", &p);
		p--;
		child[p].push_back(i);
	}
	for(auto & [l, r] : bounds) {
		scanf("%d %d", &l, &r);
	}
	printf("%d\n", dfs(0));
}


int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	test_cases();
	return 0;
}
