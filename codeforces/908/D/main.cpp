#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define range(i,a,b) for(int i = (a);i <= (b);i++)
#define all(A) A.begin(),A.end()
#define pb push_back
#define mp make_pair
#define sz(A) ((int)A.size())
#define vi vector<int>
#define vl vector<long long>
#define vd vector<double>
#define vp vector<pair<int,int> >
#define ll long long
#define pi pair<int,int>
#define popcnt(x) __builtin_popcountll(x)
#define LSOne(x) ((x) & (-(x)))
#define xx first
#define yy second
#define PQ priority_queue
#define print(A,t) cerr << #A << ": "; copy(all(A),ostream_iterator<t>(cerr," " )); cerr << endl
#define prp(p) cerr << "(" << (p).first << " ," << (p).second << ")";
#define prArr(A,n,t)  cerr << #A << ": "; copy(A,A + n,ostream_iterator<t>(cerr," " )); cerr << endl
#define PRESTDIO() cin.tie(0),cerr.tie(0),ios_base::sync_with_stdio(0)
#define what_is(x) cerr << #x << " is " << x << endl
#define bit_lg(x) (assert(x > 0),__builtin_ffsll(x) - 1)
const double PI = acos(-1);
using namespace std;

const int mod = 1000000007;

const int MAXK = 1024;


int dp[MAXK][MAXK];
int K,pa,pb,Pa,Pb;

inline int mul(int a,int b,int mod){
	return (a*1LL*b)%mod;
}
inline int add(int a,int b,int mod){
	a += b;
	if(a >= mod) a -= mod;
	if(a < 0) a += mod;
	return a;
}

inline int powmod(int a,int p,int mod) {
	a %= mod;
	if(p == 0) return 1%mod;
	int b = 1;
	for(;p > 1;p >>= 1) {
		if(p & 1) b = mul(a,b,mod);
		a = mul(a,a,mod);
	}
	return mul(a,b,mod);
}

int solve(int cnt_a,int k) {
	if(k >= K) return k;
	int & ret = dp[cnt_a][k];
	if(ret != -1) return ret;
	if(cnt_a + k >= K) {
		int res = add(cnt_a,k,mod);
		int y = powmod(Pb,mod-2,mod);
		y = mul(y,Pa,mod);
		res = add(res,y,mod);
		ret = res;
	}
	else{
		int res = 0;
		res = mul(Pa,solve(cnt_a+1,k),mod);
		if(cnt_a > 0) {
			res = add(res,mul(Pb,solve(cnt_a,k + cnt_a),mod),mod);
		}
		else{
			int x = powmod(Pa,mod-2,mod);
			res = mul(res,x,mod);
		}
		ret = res;
	}
//	cerr << cnt_a << " " << k << " " << ret << endl;
	return ret;
}

int main(){
	#ifdef HOME
		freopen("in.in", "r", stdin);
	#endif
	cin >> K >> pa >> pb ;
	memset(dp,-1,sizeof dp);
	int sc = powmod(pa + pb,mod - 2,mod);
	Pa = mul(pa,sc,mod);
	Pb = mul(pb,sc,mod);
	cout << solve(0,0) << endl;
	return 0;
}
