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


map<ll,ll> dp,dp2;

ll f(ll n){
	if(n <= 1) return 1;
	if(dp.find(n) != dp.end()) return dp[n];
	return dp[n] = 2*f(n/2) + 1;
}


ll g(ll n){
	if(n <= 1) return n;
	if(dp2.find(n) != dp2.end()) return dp2[n];
	return dp2[n] = 2*g(n/2) + (n & 1);
}

ll get(ll n,ll r){
//	cerr << n << " " << r<< endl;	
	if(f(n) <= r) return g(n);
	else{
		ll x = f(n/2);
		if(r <= x) return get(n/2,r);
		ll ret = g(n/2) ;
		r -= f(n/2);
		if(r) ret += n & 1,r--;
		if(r) ret += get(n/2,r);
		return ret;
	}
}

int main(){
	ll n,l,r;	
	cin >> n >> l >> r; l--;
//	cerr << f(n) << endl;
//	cerr << get(n,r) - get(n,l-1) << endl;
	cout << get(n,r) - (l ? get(n,l) : 0) << endl;
	
	return 0;
}
