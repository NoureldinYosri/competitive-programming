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


const int MAXN = 3000, MAXM = 8*8*8*8 + 10;

int dp[MAXN][MAXM];
int A[MAXN], n;

int solve(int i, int msk){
	if(i == n) return 0;
	int & ret = dp[i][msk];
	if(ret != -1) return ret;
	ret = 0;
	int B[4];
	loop(k, 4) {
		B[k] = msk%8;
		msk /= 8;
	}
	loop(k, 4){
		int d = B[k] - (A[i]%7);
		d = (d%7 + 7)%7;
		int tmp = B[k];
		B[k] = A[i]%7;
		int v = 0;
		loop(q, 4) v = v*8 + B[q];
		if(A[k] == 7 || d <= 1) ret = max(ret, solve(i+1, v) + 1);
		B[k] = tmp;
	}
	return ret;
}



int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	scanf("%d", &n);
	loop(i, n) scanf("%d", A + i);
	memset(dp, -1, sizeof dp);
	int m = 4095;
	cout << solve(0, m) << endl;
	return 0;
}
