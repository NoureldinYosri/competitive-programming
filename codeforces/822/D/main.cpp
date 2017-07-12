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

const int MAX = 5000*1000,mod = 1e9+ 7 ;
int f[MAX+1],g[MAX+1];
ll psi[MAX+1];
int smallest_prime[MAX+1];

void sieve(){
	fill(smallest_prime,smallest_prime + MAX + 1,INT_MAX);
	for(int i = 2;i <= MAX;i++)
		if(smallest_prime[i] == INT_MAX) {
			smallest_prime[i] = i;
			for(ll j = i*1LL*i;j <= MAX;j += i)
				smallest_prime[j] = min(smallest_prime[j],i);
		}
}

void init(){
	sieve();
	for(int i = 2;i <= MAX;i++){
		/*f[i] = INT_MAX;
		for(int j = 1;j <= i;j++)
			if(i%j == 0){
				int tmp = i*(j-1)/2 + f[i/j];
				if(f[i] > tmp) {
					f[i] = tmp;
					g[i] = j;
				}
			}*/
		ll tmp = i*(smallest_prime[i] - 1LL)/2;
		psi[i] = tmp + psi[i/smallest_prime[i]];
		psi[i] %= mod;
	}
//	for(int i = 2;i <= MAX;i++)
//		cerr << i << " " << g[i] << " " << smallest_prime[i] << " -> " << f[i] << " " << psi[i] << endl ;
//	prArr(f,MAX+1,int);
//	prArr(psi,MAX+1,ll);
}


int main(){
	#ifndef ONLINE_JUDGE
		freopen("in.in", "r", stdin);
	#endif
	init();
	int t,l,r; cin >> t >> l >> r;
	int ans = 0;
	int p = 1;
	for(;l <= r;l++){
		ans += (p*1LL*psi[l])%mod;
		p = (p*1LL*t)%mod;
	//	cerr << psi[l] << endl;
		if(ans >= mod) ans -= mod;
	}
	cout << ans << endl;
	return 0;
}
