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

const int MAX = 1000;
unordered_map<int, bool> dp[MAX][MAX];
int m, n;
int A[MAX][MAX];

void clear() {
	loop(i, m) loop(j, n) dp[i][j].clear();
}

bool solve(int i, int j, int s) {
	s += A[i][j];
	if(i == m-1 && j == n-1) return s == 0;
	int rem = m - i + n - j - 2;
	if(abs(s) > rem) return false;
	auto ptr = dp[i][j].find(s);
	if(ptr != dp[i][j].end()) return ptr->second;
	bool ret = false;
	if(i + 1 < m) ret = ret || solve(i + 1, j, s);
	if(j + 1 < n) ret = ret || solve(i, j + 1, s);
	dp[i][j][s] = ret;
	return ret;
}

void tc() {
	scanf("%d %d", &m, &n);
	loop(i, m) loop(j, n) scanf("%d", &A[i][j]);
	int len = m + n - 1;
	if(len & 1) {
		puts("NO");
		return;
	}
	puts(solve(0, 0, 0) ? "YES" : "NO");
	clear();
}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	test_cases();
	return 0;
}
