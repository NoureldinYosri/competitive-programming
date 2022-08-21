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


int n;
char G[2][1 << 20];
int dp[1 << 20][4];
int visId[1 << 20][4], visNum;
int ctr [] = {0, 1, 1, 2};

int solve(int i, int msk) {
	int & ret = dp[i][msk];
	if(visId[i][msk] == visNum) return ret;
	visId[i][msk] = visNum;
	ret = INT_MAX;
	int tot = msk | (G[0][i] == '*') | ((G[1][i] == '*') << 1);
	if(i == n-1) return ret = tot == 3;
	for(int s = tot; s; s = (s - 1) & tot) {
		ret = min(ret, solve(i + 1, s) + ctr[tot ^ s] + ctr[s]);
	}
	return ret;
}

void tc() {
	scanf("%d %s %s", &n, G[0], G[1]);
	int lst = -1, fst = -1;
	loop(i, n) if(G[0][i] == '*' || G[1][i] == '*') {
		fst = i;
		break;
	}
	loop(c, 2) rotate(G[c], G[c] + fst, G[c] + n);
	loop(i, n) if(G[0][i] == '*' || G[1][i] == '*') lst = i;
	n = lst + 1;
	visNum++;
	printf("%d\n", solve(0, 0));
}


int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	test_cases();
	return 0;
}
