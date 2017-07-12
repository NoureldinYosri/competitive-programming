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

const int MAX = 200*1000 + 10;
const int mod = 1e9 + 7;
int prime[MAX];
int cnt[MAX];
int A[MAX],n;
int p2[MAX];

void sieve(){
	for(int p = 2;p < MAX;p++)
		if(!prime[p]){
			prime[p] = p;
			for(ll x = p*1LL*p;x < MAX;x += p)
				prime[x] = p;
		}
}

int main(){
	#ifndef ONLINE_JUDGE
		freopen("in.in", "r", stdin);
		freopen("out.out", "w", stdout);
	#endif
	sieve();
	p2[0] = 1;
	for(int i = 1;i < MAX;i++) {
		p2[i] = p2[i - 1] + p2[i - 1];
		if(p2[i] >= mod) p2[i] -= mod;
	}
	scanf("%d",&n);
	vi P;
	ll ans = 0;
	loop(i,n){
		scanf("%d",A + i);
		P.clear();
		for(int x = A[i];x > 1;){
			int p = prime[x];
			P.pb(p);
			while(x%p == 0) x /= p;
		}
		ll tmp = 0;
		loop(msk,1 << sz(P)) if(msk){
			int sgn = -1,div = 1;
			loop(i,sz(P)) if(msk & (1 << i)){
				div *= P[i];
				sgn *= -1;
			}
			tmp += sgn * p2[cnt[div]];
			if(tmp >= mod) tmp -= mod;
			if(tmp < 0) tmp += mod;
		}
		ans += tmp;
		if(ans >= mod) ans -= mod;
		if(ans < 0) ans += mod;
		loop(msk,1 << sz(P)) if(msk){
			int div = 1;
			loop(i,sz(P)) if(msk & (1 << i)){
				div *= P[i];
			}
			cnt[div]++;
		}
	}
	ans = p2[n] - ans - 1;
	ans = (ans%mod + mod)%mod;
	cout << ans << endl;
	cerr << ans << endl;
	return 0;
}
