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


int H[300], n;
int dp[300][222][222];

int solve(int i, int h0, int h1){
	if(i == n) return 0;
	h0 = min(h0, 200);
	h1 = min(h1, 200);
	int & ret = dp[i][h0][h1];
	if(ret != -1) return ret;
	int r = max(H[i] - h0, 0);
	ret = 1 << 29;
	if(r == 0) ret = solve(i + 1, h1, 0);
	else {
		ret = 3 + solve(i, h0 + 1, h1);
		ret = min(ret, 5 + solve(i, h0 + 1, h1 + 1));
		ret = min(ret, 7*r + solve(i + 1, h1 + r, r));
	}
//	cerr << i << " " << pi(h0, h1) << ": " << ret << endl;
	return ret;
}


int main(){
	freopen("skyline.in", "r", stdin);
#ifndef HOME
	freopen("skyline.out", "w", stdout);
#endif
	scanf("%d", &n);
	loop(i, n) scanf("%d", H + i);
	memset(dp, -1, sizeof dp);
	cout << solve(0, 0, 0) << endl;
	return 0;
}
