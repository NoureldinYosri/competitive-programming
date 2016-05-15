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

const ll mod = 1e9 + 7;

ll pmod(ll b,ll p){
	if(p == 0) return 1;
	ll ret = b,tmp = 1;
	while(p > 1){
		if(p & 1) tmp = (tmp * ret)%mod;
		ret = (ret * ret)%mod;
		p >>= 1;
	}	
	ret = (ret * tmp)%mod;
	return ret;
}

ll Y[1 << 20];

int main(){
	ll n,k;
	cin >> n >> k;
	for(ll i = 1;i <= k + 1;i++) {
		Y[i] = (Y[i - 1] + pmod(i,k))%mod;
	}	
	if(n <= k + 1){
		cout << Y[n] << endl;
		return 0;
	}
	ll A = 1,B = 1;
	queue<ll> q;
	for(ll i = 0;i <= k + 1;i++) A = (A*(n - i)) % mod;
	for(ll i = k + 1;i;i--) {
		B = (B * (mod-i))%mod;
		q.push(mod-i);	
	}
	ll ans = 0;
	for(ll i = 0;i <= k + 1;i++){
		ll a = A * pmod(n - i,mod - 2);
		a %= mod;
		a = (a * pmod(B,mod - 2))%mod;
		ans = (ans + a *Y[i])%mod;
		B = (B * pmod(q.front(),mod - 2))%mod;
		q.pop();
		q.push(i + 1);
		B = (B * (i + 1))%mod;
	}
	cout << ans << endl;
	return 0;
}	
