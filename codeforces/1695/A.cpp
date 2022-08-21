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

const int MAXN = 40;
int G[MAXN][MAXN];
int B[MAXN][MAXN];
int m, n;

bool check(int h, int w) {
	for(int i = 0; i <= m - h; i++)
		for(int j = 0; j <= n - w; j++) {
			int ctr = B[i + h - 1][j + w - 1];
			if(i) ctr -= B[i - 1][j + w - 1];
			if(j) ctr -= B[i + h - 1][j - 1];
			if(i && j) ctr += B[i - 1][j - 1];
			assert(ctr >= 0);
			if(ctr == 0) return false;
		}
	return true;
}

void tc() {
	scanf("%d %d", &m, &n);
	int target = INT_MIN;
	loop(i, m) loop(j, n) {
		scanf("%d", &G[i][j]);
		target = max(target, G[i][j]);
	}
//	cerr << "target = " << target << endl;
	loop(i, m) loop(j, n) {
		B[i][j] = G[i][j] == target;
		if(i) B[i][j] += B[i - 1][j];
		if(j) B[i][j] += B[i][j - 1];
		if(i && j) B[i][j] -= B[i - 1][j - 1];
	}
	int ans = m*n;
	for(int h = 1; h <= m; h++)
		for(int w = 1; w <= n; w++)
			if(check(h, w)) {
				ans = min(ans, h*w);
		//		cerr << h << " x " << w << endl;
			}
	printf("%d\n", ans);
}


int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	test_cases();
	return 0;
}
