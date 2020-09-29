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

const int MAX = 1000*1000, MAXR = 6;

int dp[MAX+2][MAXR+1][MAXR+1];
int freq[MAX+1];

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	int n, m; scanf("%d %d", &n, &m);
	for (int i = 0;i < n;i++){
		int x; scanf("%d", &x);
		freq[x] ++;
	}
	for (int i = m;i >= 1;i--) {
		for (int p = 0;p <= MAXR;p++)
			for(int pp = 0;pp <= MAXR;pp++) {
				int ret = 0;
				int r = min(freq[i],MAXR);
				int k = (freq[i] - r)/3,r2 = freq[i] - 3*k - r;
				for(int j = 0;j <= r;j++) {
					int aux = min(j, min(p,pp));
					int aux2 = (j + r2 - aux)/3;
					ret = max(ret,dp[i+1][r-j][p-aux] + aux + aux2);
				}
				ret += k;
				dp[i][p][pp] = ret;
			}
	}
	cout << dp[1][0][0] << endl;
	return 0;
}
