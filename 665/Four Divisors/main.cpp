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

const int MAX = 1 << 20;
vi P;
int not_prime[MAX];
vl cube;

void sieve(){
	for(int p = 2;p < MAX;p++)
		if(!not_prime[p]){
			P.pb(p);
			for(ll x = p*1LL*p;x < MAX;x += p)
				not_prime[x] = 1;
		}
}


int main(){
	#ifndef ONLINE_JUDGE
		freopen("in.in", "r", stdin);
	#endif
	sieve();
	ll n ; cin >> n;
	for(int p : P){
		ll sq = p*1LL*p;
		ll cu = sq*p;
		if(cu <= n) cube.pb(cu);
	}
	print(cube,ll);
	int ans = sz(cube) + 1;
	for(int p : P){
		// #primes p' | p < p' <= n/p
		if(n/p <= p) break;

	}
	cout << ans << endl;
	return 0;
}
