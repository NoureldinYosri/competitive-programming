#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define range(i,a,b) for(int i = (a);i <= (b);i++)
#define all(A) A.begin(),A.end()
#define pb push_back
#define mp make_pair
#define sz(A) ((int)A.size())
#define vi vector<int>
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
using namespace std;

const int MAX = 100*1000 + 10,mod = 1e9 + 7;
int dp[16][MAX],s;
ll k;

int mul(int a,int b) {
	return (a*1LL*b)%mod;
}
int add(int a,int b) {
	a += b;
	if(a >= mod) a -= mod;
	if(a < 0) a += mod;
	return a;
}
int powmod(int x,ll p) {
	if(p == 0) return 1;
	int y = 1;
	for(;p > 1;p >>= 1) {
		if(p & 1) y = mul(x,y);
		x = mul(x,x);
	}
	return mul(x,y);
}

int num_pal(ll n) {
	ll f = n/2;
	int ret = 1;
	// 10^i i = 0..(f-1)
	int tmp = add(powmod(10,f),-1);
	ret = add(ret,tmp);
	ret = add(ret,tmp);
	if(n&1){
		f++;
		ret = add(ret,mul(9,powmod(10,f-1)));
	}
	return ret;
}

int num2(ll n) {
	ll f = n/2;
	int ret = num_pal(n);
	// 4 * 5^(f-1)
	int tmp = add(powmod(5,f),-1);
	ret = add(ret,-tmp);
	ret = add(ret,-tmp);
	if(n&1) {
		f++;
		ret = add(ret,mul(4,powmod(5,f-1)));
	}
	return ret;
}


int solve() {
	return -1;
}

int main(int argc,char **argv){
#ifdef HOME
	freopen("in.in","r",stdin);
#endif
	int T; scanf("%d",&T);
	while(T--) {
		scanf("%d %lld",&s,&k);
		int ans = 0;
		if(s == 1) ans = num_pal(k);
		else if(s == 2) ans = num2(k);
		else if(k < MAX) ans = solve();
		printf("%d\n",ans);
	}

	return 0;
}
