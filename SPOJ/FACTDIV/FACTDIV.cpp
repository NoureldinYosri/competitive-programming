#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define range(i,a,b) for(int i = (a);i <= (b);i++)
#define rrep(i,n) for(int i = (n);i >= 0;i--)
#define rran(i,a,b) for(int i = (b);i >= (a);i--)
#define step(i,a,b,d) for(int i = (a);i <= (b); i += d)
#define all(A) A.begin(),A.end()
#define PI acos(-1)
#define pb push_back
#define mp make_pair
#define sz(A) A.size()
#define len(A) A.length()
#define vi vector<int>
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
#define pre() cin.tie(0),cerr.tie(0),ios_base::sync_with_stdio(0)
using namespace std;

const int MAX = 1000000;
const ll mod = 1e9 + 7;
int fun[MAX + 1];
int prime_div[MAX + 1];
int ctr[MAX + 1];
int inv[MAX + 1];

void sieve(){
	for(int n = 1;n <= MAX;n++) prime_div[n] = n;	
	for(int n = 2;n <= MAX;n++){
		if(prime_div[n] == n){
			for(ll j = n*1LL*n;j < MAX;j += n)
				prime_div[j] = n;
		}
	}
}

void mod_inv(){
	inv[1] = 1;
	for(int n = 2;n <= MAX;n++)
		inv[n] = (mod - (mod/n) * inv[mod%n] % mod) % mod;
}

int EXP(int p,int q,int m = mod){
	ll A = p,B = 1;
	while(q > 1){
		if(q & 1) B = (A*B)%m;
		A = (A*A)%m;
		p >>= 1;
	}
	return (A*B)%m;
}

void init(){
	ll sig = 1;
	fun[0] = 1; fun[1] = 2;
	for(int n = 2;n <= MAX;n++){
		if(prime_div[n] == n){
			ctr[n] = 1;
			sig <<= 1;
			if(sig >= mod) sig -= mod;	
		}
		else{
			int m = n;
			while(m > 1){
				int p = prime_div[m];
				sig *= inv[ctr[p] + 1]; sig %= mod;				
				while(m % p == 0){
					ctr[p]++;
					m /= p;
				}
				sig *= (ctr[p] + 1); sig %= mod;
			}
		}
		fun[n] = fun[n - 1] + sig;
		if(fun[n] >= mod) fun[n] -= mod;
	}	
}

int main(){
	sieve();
	mod_inv();
	init();
	int T,l,r;
	scanf("%d",&T);
	while(T--){
		scanf("%d %d",&l,&r); 
		int res = fun[r] - fun[l - 1];
		while(res < 0) res += mod;
		while(res >= mod) res -= mod;
		printf("%d\n",res);
	}
	return 0;
}
