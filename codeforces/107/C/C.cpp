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

vector<ll> D;
vector<ll> primes;
map<ll,pl> dp;

int solve(ll n,ll & mv){
	if(n == 1 || binary_search(all(primes),n)){
		mv = 0;
		return 1;
	}
	if(dp.find(n) != dp.end()){
		mv = dp[n].yy;
		return dp[n].xx;
	}
	for(auto v : D){
		if(v >= n) break;
		if(n%v == 0){
			if(!solve(v,mv)){
				mv = v;
				dp[n] = mp(1,v);
				return 1;
			}	
		}
	}
	mv = 0;
	dp[n] = mp(0,0);
	return 0;
}

void get_primes(ll n){
	for(ll i = 2;i*i <= n;i++){
		if(n%i == 0){
			primes.pb(i);
			while(n%i == 0) n /= i;
		}
	}
	if(n > 1) primes.pb(n);
}

int main(){
	ll n;
	cin >> n;
	for(ll i = 2;i*i <= n;i++){
		if(n%i == 0){
			D.pb(i);
			if(i*i != n) D.pb(n/i);
		}
	}
	sort(all(D));
	get_primes(n);	
	ll mv;
	if(solve(n,mv)) cout << 1 << endl << mv << endl;
	else cout << 2 << endl;	
	return 0;
}
