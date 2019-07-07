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

const int MAX = 1 << 20;
int dp[MAX],A[MAX],n;
vi divs[MAX];
int prime[MAX];

void sieve(){
	divs[1].pb(1);
	for(int i = 2;i < MAX;i++) {
		if(!prime[i]) {
			prime[i] = i;
			for(ll j = i*(ll)i;j < MAX;j += i)
				prime[j] = i;
		}
		int n = i,p = prime[i],e = 0;
		while(n%p == 0) n/=p,e++;
		for(int q = 1;e >= 0;e--,q *= p)
			for(int d : divs[n])
				divs[i].pb(d*q);
		sort(all(divs[i]));
		reverse(all(divs[i]));
	}
}

int mod = 1000000007;
int add(int a,int b) {
	a += b;
	if(a >= mod) a -= mod;
	return a;
}

int main(int argc,char **argv){
#ifdef HOME
	freopen("in.in","r",stdin);
#endif
	sieve();
	scanf("%d",&n);
	loop(i,n) scanf("%d",A + i);
	dp[0] = 1;
	loop(i,n){
		int b = A[i];
		for(int d : divs[b])
			dp[d] = add(dp[d],dp[d - 1]);
	}
	int ans = 0;
	for(int i = 1;i <= n;i++)
		ans = add(ans,dp[i]);
	cout << ans << endl;
	return 0;
}
