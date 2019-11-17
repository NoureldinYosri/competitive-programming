#ifdef ACTIVE
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
#define tc() int T; scanf("%d",&T); for(int t = 1;t <= T;t++)
using namespace std;

const int mod = 1000000007;
int add(int a,int b) {
	a += b;
	if(a >= mod) a -= mod;
	return a;
}
int mul(int a,int b){
	return (a*(ll)b)%mod;
}
const int MAX = 300;

int powers[MAX];
int C[MAX][MAX];
int dp[MAX][MAX];

void init(int ik){
	for(int n = 0;n < MAX;n++) {
		C[n][0] = C[n][n] = 1;
		for(int k = 1;k < n;k++)
			C[n][k] = add(C[n-1][k],C[n-1][k-1]);
	}
	int k_neg = ik - 1;
	powers[0] = 1;
	for(int i = 1;i < MAX;i++)
		powers[i] = mul(powers[i-1],k_neg);
}

int coef[MAX][MAX];

int solve(int n) {
	loop(rem,n+1) dp[0][rem] = rem == 0;

	for(int rem = 0;rem <= n;rem++) {
		for(int a = 0;a <= rem;a++){
			int & res = coef[rem][a];
			res = 0;
			for(int b = a==0;b <= n-a;b++){
				int tmp = mul(C[rem][a],C[n-rem][b]);
				tmp = mul(tmp,powers[n-a-b]);
				res = add(res,tmp);
			}
		}
	}

//	assert(n < MAX);
	for(int c = 1;c <= n;c++){
		for(int rem = 0;rem <= n;rem++) {
			int & res = dp[c][rem];
			res = 0;
			for(int a = 0;a <= rem;a++) {
				res = add(res,mul(coef[rem][a],dp[c-1][rem-a]));
			}
		}
//		prArr(dp[c],n+1,int);
	}
	return dp[n][n];
}


int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	int n,k;
	cin >> n >> k;
	init(k);
	cout << solve(n) 	 << endl;
	return 0;
}
#endif
