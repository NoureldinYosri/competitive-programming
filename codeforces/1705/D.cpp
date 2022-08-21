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


char patt[1 << 20], txt[1 << 20];
int n;
bool needChange[1 << 20], canChange[1 << 20];

void dfs(int i) {
	if(i==0 || i==n-1 || canChange[i]) return;
	canChange[i] = true;
	dfs(i - 1);
	dfs(i + 1);
}

int pref[1 << 20][2];
int suff[1 << 20][2];

int solvePrefix(int i, int c) {
	if(i == 0) return 0;
	int & ret = pref[i][c];
	if(ret != -1) return ret;
	ret = 1 << 25;
	char ch = '0' + c;
	if(txt[i] == patt[i]) {
		ret = min(ret, solvePrefix(i - 1, patt[i] - '0'));
		if(ch != txt[i - 1] && ch != patt[i - 1]) {
			ret = min(ret, 2 + solvePrefix(i - 1, 1 - (txt[i] - '0')));
		}
	} else {
		if(ch != txt[i - 1]) ret = min(ret, 1 + solvePrefix(i - 1, patt[i] - '0'));
		if(ch != patt[i - 1]) ret = min(ret, 1 + solvePrefix(i - 1, txt[i] - '0'));
	}
	return ret;
}

int solveSuff(int i, int c) {
	if(i == n-1) return 0;
	int & ret = suff[i][c];
	if(ret != -1) return ret;
	ret = 1 << 25;
	char ch = '0' + c;
	if(txt[i] == patt[i]) {
		ret = min(ret, solveSuff(i + 1, patt[i] - '0'));
		if(ch != txt[i + 1] && ch != patt[i + 1]) {
			ret = min(ret, 2 + solveSuff(i + 1, 1 - (txt[i] - '0')));
		}
	} else {
		if(ch != txt[i + 1]) ret = min(ret, 1 + solveSuff(i + 1, patt[i] - '0'));
		if(ch != patt[i + 1]) ret = min(ret, 1 + solveSuff(i + 1, txt[i] - '0'));
	}
	return ret;
}


int solve() {
	if(strcmp(txt, patt) == 0) return 0;
	if(txt[0] != patt[0] || txt[n-1] != patt[n-1]) return -1;
	loop(i, n) loop(c, 2) pref[i][c] = suff[i][c] = -1;
	int ans = 1 << 25;
	for(int i = 1; i + 1 < n; i++) {
		if(txt[i - 1] == txt[i + 1]) continue;
		int a = solvePrefix(i - 1, 0) + solveSuff(i + 1, 0);
		int b = solvePrefix(i - 1, 1) + solveSuff(i + 1, 1);
		if(txt[i] == '1') swap(a, b);
		// cerr << i << ": " << a << " " << b << endl;
		bool mustChange = txt[i] != patt[i];
		int tmp = 1 << 25;
		if(mustChange) {
			tmp = 1 + b;
			if(patt[i - 1] != patt[i + 1])
				tmp = min(tmp, 1 + a);
		} else {
			tmp = a;
			if(patt[i - 1] != patt[i + 1])
				tmp = min(tmp, b + 2);
		}
		ans = min(ans, tmp);
	}
	if(ans >= (1 << 25)) ans = -1;
	return ans;
}

void tc() {
	scanf("%d %s %s", &n, txt, patt);
	printf("%d\n", solve());
}


int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	test_cases();
	return 0;
}
