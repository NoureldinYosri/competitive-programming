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
#define pl pair<ll,ll>
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

const int mod = 1e9 + 7 ;

#define mul(a,b) (((a)*1LL*(b))%mod)
#define add(a,b) (aux = a+b,aux -= (aux >= mod) ? mod : 0)
int pow_mod(int x,int p){
	if(!p) return 1;
	int y = 1;
	for(;p > 1;p >>= 1) {
		if(p & 1) y = mul(x,y);
		x = mul(x,x);
	}
	return mul(x,y);
}


const int MAX = 1500;
int dp[500][MAX];
int f[MAX],r[MAX],aux;

#define C(n,k) ((n<k) ? 0 : mul(f[n],mul(r[k],r[n-k])))


int main(){
	#ifndef ONLINE_JUDGE
		freopen("in.in", "r", stdin);
	#endif
	int k; scanf("%d",&k);
	dp[1][0] = dp[1][1] = 1;
	f[0] = r[0] = 1;
	loop(i,MAX-1) {
		f[i+1] = mul(f[i],i+1);
		r[i+1] = pow_mod(f[i+1],mod-2);
	}
	int lim = k+1,x,y;
	range(n,2,k) {
		int cur_lim = lim,n_lim = lim;
		if(n-1 < 8) cur_lim = (1 << n) >> 1,n_lim = (1 << n);
	    range(a,0,cur_lim)
	        range(b,0,cur_lim){
	    		if(a + b > n_lim) break;
	            int p = mul(dp[n - 1][a],dp[n-1][b]);
	            if ((a + b + 1) < n_lim) dp[n][a + b + 1] = add(dp[n][a + b + 1],p);
	            x = (a << 1) + (b << 1) + 1;
	            dp[n][a+b] = add(dp[n][a+b],mul(x,p));
				if (a + b > 0)
					dp[n][a+b-1] = add(dp[n][a+b-1],mul(p,mul(2,C(a+b,2))));
	    	}
	}
	cout << dp[k][1] << endl;
	return 0;
}


