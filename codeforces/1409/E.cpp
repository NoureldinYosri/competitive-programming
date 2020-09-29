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

const int MAXN = 200*1000 + 10;
int n, K;
int X[MAXN], Y[MAXN];
int dp[MAXN][2];
int visID[MAXN][2], visNum;
int nxt[MAXN];

int solve(int i, int k){
	if(k == 2 || i == n) return 0;
	int & ret = dp[i][k];
	if(visID[i][k] == visNum) return ret;
	visID[i][k] = visNum;
	ret = solve(i + 1, k);
	ret = max(ret, nxt[i] - i + solve(nxt[i], k + 1));
	return ret;
}

void tc(){
	scanf("%d %d", &n, &K);
	loop(i, n) scanf("%d", X + i);
	loop(i, n) scanf("%d", Y + i);
	visNum++;
	sort(X, X + n);
	int j = 0;
	loop(i, n){
		while(j < n && X[i] + K >= X[j]) j++;
		nxt[i] = j;
	}
//	prArr(X, n, int);
//	prArr(nxt, n, int);
	printf("%d\n", solve(0, 0));
}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	int T; scanf("%d", &T);
	while(T--) tc();
	return 0;
}
