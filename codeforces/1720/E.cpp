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

const int MAX = 512;
int n, m;
int G[MAX][MAX];
vp idx[MAX*MAX];

int solve() {
	vi A;
	loop(i, n) loop(j, m) A.push_back(G[i][j]);
	sort(all(A));
	A.resize(unique(all(A)) - A.begin());
	if(sz(A) <= m) return m - sz(A);

	int tot = sz(A);
	loop(i, n) loop(j, n) idx[G[i][j]].emplace_back(i, j);

	map<int, vp> crticial;
	for(int a : A) {
		int mx_i = idx[a].back().first;
		int mn_i = idx[a][0].first;
		int mx_j = -1, mn_j = INT_MAX;
		for(auto [_, j] : idx[a]) {
			mn_j = min(mn_j, j);
			mx_j = max(mx_j, j);
		}
		int k = max(mx_j - mn_j, mx_i - mn_i) + 1;
		crticial[k].emplace_back(mn_i, mn_j);
	}

	sort(crticial.rbegin(), crticial.rend());
	for(int s = 1; s <= n; s++) {
		for(auto [i, j] : crticial[s])
			active[i][j]++;
				
	}
	return 2;
}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	scanf("%d %d", &n, &m);
	loop(i, n) loop(j, m) scanf("%d", &G[i][j]);
	cout << solve() << endl;
	return 0;
}
