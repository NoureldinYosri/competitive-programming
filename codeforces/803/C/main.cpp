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

int main(){
	#ifndef ONLINE_JUDGE
		freopen("in.in", "r", stdin);
		freopen("out.out", "w", stdout);
	#endif
	ll n,k; cin >> n >> k;
	vector<ll> divs;
	for(ll d = 1;d*d <= n;d++){
		if(n%d == 0){
			divs.pb(d);
			if(d*d != n){
				divs.pb(n/d);
			}
		}
	}
	sort(all(divs));
	reverse(all(divs));
	ll mn = k*(k + 1)/2;
	for(ll g : divs){
		ll target = n/g;
		if(target >= mn){
			for(int i = 1;i < k;i++)
				printf("%lld ",i*g);
			ll r = target - k*(k - 1)/2;
			printf("%lld\n",r*g);
			return 0;
		}
	}
	puts("-1");

	return 0;
}
