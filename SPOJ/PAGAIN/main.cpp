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

const int MAXITR = 10;


unsigned int pow_mod(unsigned int x,unsigned int p,unsigned int mod){
	if(!p) return 1;
	ll y = 1;
	for(;p > 1;p >>= 1){
		if(p & 1) y = (x*1LL*y)%mod;
		x = (x*1LL*x)%mod;
	}
	return (x*1LL*y)%mod;
}

bool is_probable_prime(unsigned int n){
	if(n <= 1) return 0;
	if(n <= 3) return 1;
	if(n%2 == 0 || n%3 == 0) return 0;
	for(int i = 0;i < MAXITR;i++){
		unsigned int x = rand()%(n - 1) + 1;
		if(__gcd(x,n) != 1) return 0;
		if(pow_mod(x,n-1,n) != 1) return 0;
	}
	return 1;
}

int main(){
	#ifndef ONLINE_JUDGE
		freopen("in.in", "r", stdin);
	#endif
	int T; scanf("%d",&T);
	while(T--){
		unsigned int n ; scanf("%u",&n);
		for(--n;!is_probable_prime(n);n--);
		printf("%lld\n",n);
	}
	return 0;
}
