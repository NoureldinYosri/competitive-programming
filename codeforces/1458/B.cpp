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

const int MAXN = 111, MAXA = 211;
int n;
int A[MAXN], B[MAXN];
int dp[2][MAXN][2*MAXN*MAXA + 1];
int visNum;
int visId[2][MAXN][2*MAXN*MAXA + 1];



int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	scanf("%d", &n);
	loop(i, n) {
		scanf("%d %d", A + i, B + i);
		A[i] <<= 1;
		B[i] <<= 1;
	}
	int sum = accumulate(A, A + n, 0);
	
	int cur = 0, other = 1;
	for(int s = -sum; s <= sum; s++)
		for(int k = 0; k <= n; k++)
			dp[cur][k][s + sum] = min(s, 0);
			
	for(int i = 0; i < n; i++){
		swap(cur, other);
		for(int k = 0; k <= n; k++){
			for(int s = -sum; s <= sum; s++){
				int & ret = dp[cur][k][s + sum];
				ret = -(1 << 29);
				if((s-(B[i]>>1)+sum) >= 0)
					ret = dp[other][k][s - (B[i] >> 1) + sum] + (B[i] >> 1);
				if(k && (s + A[i]-B[i]) <= sum) 
					ret = max(ret, dp[other][k-1][s + A[i] - B[i] + sum] + B[i]);	
			}
		}
	}

	for(int k = 1; k <= n; k++){
		int ans = dp[cur][k][sum];
		printf("%d.%d%c", ans >> 1, (ans&1)*5, " \n"[k==n]);
	}
	return 0;
}
