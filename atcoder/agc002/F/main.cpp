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

const int MAX = 2000 + 10,MAXF = 2000*2000 + 10;
const int mod = 1e9 + 7;
int fact[MAXF],rev[MAXF];
int dp[MAX][MAX];

inline int add(int a,int b) {
	a += b;
	if(a >= mod) a -= mod;
	return a;
}
inline int mul(int a,int b) {return (a*1LL*b)%mod;}
inline int powmod(int a,int p) {
	if(p <= 0) return 1;
	int b = 1;
	for(;p > 1;p >>= 1) {
		if(p&1) b = mul(a,b);
		a = mul(a,a);
	}
	return mul(a,b);
}

void init(){
	fact[0] = rev[0] = 1;
	for(int i = 1;i < MAXF;i++) {
		fact[i] = mul(fact[i - 1],i);
		rev[i] = powmod(fact[i],mod-2);
	}
}

int C(int n,int k) {
	if(k > n) return 0;
	int ret = fact[n];
	ret = mul(ret,rev[k]);
	ret = mul(ret,rev[n - k]);
	return ret;
}

int main(){
	#ifdef HOME
		freopen("in.in", "r", stdin);
	#endif
	init();
	int N,K;
	cin >> N >> K;
	if(K == 1) {
		cout << 1 << endl;
		return 0;
	}
    for (int r1 = N+1;r1 >= 1;r1--)
        for (int r2 = N+1;r2 >= 1;r2--) {
            if(r1 == N+1 && r2 == N+1) dp[r1][r2] = 1;
            else if(r2 > r1) dp[r1][r2] = 0;
            else {
                int ret = 0;
                if(r1 <= N) ret = dp[r1+1][r2];
                if(r2 < r1) ret = add(ret,mul(dp[r1][r2+1],C(N*K-(r1-1)-(r2-1)*(K-1)-1,K-2)));
                dp[r1][r2] = ret;
            }
        }
    int ans = mul(dp[1][1],fact[N]);
    cout << ans << endl;
	return 0;
}
