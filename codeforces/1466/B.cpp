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

const int MAXN = 1 << 20;
int n, A[MAXN];
int visId[MAXN][2], visNum;
int dp[MAXN][2];

int solve(int i, int c){
	assert(c >= 0 && c <= 1);
	if(i == n) return 0;
	if(visId[i][c] == visNum) return dp[i][c];
	visId[i][c] = visNum;
	int & ret = dp[i][c];
	ret = 0;
	int prv = i ? A[i - 1] : (-(1 << 29));
	loop(t, 2){
		if(prv + c > A[i] + t) continue;
		int tmp = solve(i + 1, max(prv + c, A[i] + t) - A[i]) + (prv+c != A[i]+t);
		ret = max(ret, tmp);
	}
	return ret;
}

void tc(){
	scanf("%d", &n);
	loop(i, n) scanf("%d", A + i);
	if(!is_sorted(A, A + n)) sort(A, A + n);
	visNum++;
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
