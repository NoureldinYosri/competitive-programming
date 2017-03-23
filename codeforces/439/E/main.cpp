#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define range(i,a,b) for(int i = (a);i <= (b);i++)
#define all(A) A.begin(),A.end()
#define PI acos(-1)
#define pb push_back
#define mp make_pair
#define sz(A) ((int)A.size())
#define vi vector<int>
#define vl vector<long long>
#define vd vector<double>
#define vp vector<pair<int,int> >
#define ll long long
#define pi pair<int,int>
#define point pair<double,double>
#define pl pair<ll,ll>
#define popcnt(x) __builtin_popcount(x)
#define LSOne(x) ((x) & (-(x)))
#define xx first
#define yy second
#define PQ priority_queue
#define print(A,t) cerr << #A << ": "; copy(all(A),ostream_iterator<t>(cerr," " )); cerr << endl
#define prp(p) cerr << "(" << (p).first << " ," << (p).second << ")";
#define prArr(A,n,t)  cerr << #A << ": "; copy(A,A + n,ostream_iterator<t>(cerr," " )); cerr << endl
#define PRESTDIO() cin.tie(0),cerr.tie(0),ios_base::sync_with_stdio(0)
using namespace std;

const int MAX = 1e5 + 1e2,mod = 1e9 + 7;
int fact[MAX],inv[MAX];
int prime[MAX];

int mul(int a,int b){
	return (a * 1LL *b)%mod;
}
int add(int a,int b){
	a += b;
	if(a >= mod) a -= mod;
	if(a < 0) a += mod;
	return a;
}

int POW(int a,int p){
	if(!p) return 1;
	int b = 1;
	for(;p > 1; p >>= 1){
		if(p & 1) b = mul(b,a);
		a = mul(a,a);
	}
	return mul(a,b);
}

void sieve(){
	range(i,2,MAX-1){
		if(prime[i] == 0){
			prime[i] = i;
			for(ll j = i*1LL*i;j < MAX;j += i)
				prime[j] = i;
		}
	}
}

void init(){
	fact[0] = inv[0] = 1;
	loop(i,MAX - 1){
		fact[i + 1] = mul(fact[i],i + 1);
		inv[i + 1] = POW(fact[i + 1],mod - 2);
	}
	sieve();
}

int get(int n,int k){
	if(k > n) return 0;
	int ret = fact[n - 1];
	ret = mul(ret,inv[k - 1]);
	ret = mul(ret,inv[n - k]);
	return ret;
}



int main(){
	init();
	int T,n,f; scanf("%d",&T);
	while(T--){
		scanf("%d %d",&n,&f);
		int ans = 0,N = n;
		vi P;
		while(n > 1){
			int p = prime[n];
			P.pb(p);
			while(n%p == 0) n /= p;
		}
		n = N;
		loop(msk,1 << sz(P)){
			int sgn = 1,d = 1;
			loop(i,sz(P)) if(msk & (1 << i)){
				sgn *= -1;
				d *= P[i];
			}
			ans = add(ans,sgn * get(n/d,f));
		}
		printf("%d\n",ans);
	}
	return 0;
}
