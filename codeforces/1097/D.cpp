#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define all(A) A.begin(),A.end()
#define pb push_back
#define mp make_pair
#define sz(A) ((int)A.size())
typedef std::vector<int> vi;
typedef std::pair<int,int> pi;
typedef std::vector<pi> vp;
typedef long long ll;
#define popcnt(x) __builtin_popcount(x)
#define LSOne(x) ((x) & (-(x)))
#define print(A,t) cerr << #A << ": "; copy(all(A),ostream_iterator<t>(cerr," " )); cerr << endl
#define prArr(A,n,t)  cerr << #A << ": "; copy(A,A + n,ostream_iterator<t>(cerr," " )); cerr << endl
#define PRESTDIO() cin.tie(0),cerr.tie(0),ios_base::sync_with_stdio(0)
#define what_is(x) cerr << #x << " is " << x << endl
#define bit_lg(x) (assert(x > 0),__builtin_ffsll(x) - 1)
const double PI = acos(-1);
template<class A,class B>
std::ostream& operator << (std::ostream& st,const std::pair<A,B> p) {
	st << "(" << p.first << ", " << p.second << ")";
	return st;
}
using namespace std;

const int mod = 1e9 + 7;
const int MAXK = 10*1000 + 10;
ll n;
int K;
vi invInt;
vector<ll> divs;
vector<vi> adj, dp;


int add(int a, int b){
	a += b;
	if(a >= mod) a -= mod;
	return a;
}
int mul(int a, int b){
	return (a*(ll)b)%mod;
}




int solve(int k, int i){
	if(k == 0) return divs[i]%mod;
	int & ret = dp[k][i];
	if(ret != -1) return ret;
	ret = 0;
	for(int j : adj[i]) ret = add(ret, solve(k-1, j));
	ret = mul(ret, invInt[sz(adj[i])]);
	return ret;
} 

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	cin >> n >> K;
	
	for(ll i = 1; i*i <= n; i++) if(n%i == 0){
		divs.push_back(i);
		if(i != n/i) divs.push_back(n/i);
	}
	
	cerr << divs.size() << endl;
	sort(all(divs));
	dp.resize(2, vi(sz(divs), -1));
	adj.resize(sz(divs));
	int m = 0;
	loop(i, sz(divs)) loop(j, i) if(divs[i]%divs[j] == 0) {
		adj[i].pb(j);
		m++;
	}
	cerr << m << endl;
	invInt.resize(sz(divs) + 1);
	invInt[1] = 1;
	for(int i = 2; i <= sz(divs); i++)
		invInt[i] = mod - mul(mod/i, invInt[mod%i]);
	
	
	
	//cout << dp[cur].back() << endl;
	
	return 0;
}
