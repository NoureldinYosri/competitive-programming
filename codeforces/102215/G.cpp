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
#define tc() int T; scanf("%d",&T); for(int t = 1;t <= T;t++)
using namespace std;



ll A[1 << 20];
int n,k;

int getS(int k) {
	if(k <= 25) return 1 << k;
	return 1 << 25;
}

ll solve(vector<ll> & V,int k) {
	if(sz(V) <= 1) return 0;
	ll sum = accumulate(all(V),0LL);
	int c = -1;
	ll best = LLONG_MIN;
	ll s = 0;
	int S = getS(k-1);
	for(int i = 0;i < sz(V);i++) {
		s += V[i];
		if(i+1 <= S && sz(V)-i-1 <= S) {
			ll other = sum - s;
			ll diff = other - s;
//			if(sz(V) == 5) cout << s << " " << other << " " << diff << " " << i << endl;
			if(diff > best){
				best = diff;
				c = i;
			}
		}
	}
	assert(c != -1);
	vector<ll> A{V.begin(),V.begin() + c + 1};
	vector<ll> B{V.begin() + c + 1,V.end()};
	return sum + solve(A,k-1) + solve(B,k-1);
}


ll dfs(int u,map<int,pi> & M,vector<ll> & V,int & H,int d = 1) {
	H = max(H,d);
	if(u < sz(V)) return V[u]*d;
	return dfs(M[u].first,M,V,H,d+1) + dfs(M[u].second,M,V,H,d+1);
}

vector<ll> V;

priority_queue<pair<ll,int>,vector<pair<ll,int>>,greater<pair<ll,int>>> pq;
pair<ll,int> huffman(int s,int e) {
	if(s == e) return mp(0,0);
	while(!pq.empty()) pq.pop();
	for(int i = s;i <= e;i++)
		pq.emplace(V[i],i);
	map<int,pi> M;
	int n = sz(V);
	while(sz(pq) > 2) {
		auto u = pq.top(); pq.pop();
		auto v = pq.top(); pq.pop();
		ll s = u.first + v.first;
		pq.emplace(s,n);
		M[n] = pi(u.second,v.second);
//		cout << n << " " << M[n] << endl;
		n++;
	}
	ll ret = 0;
	int H = 0;
	ret += dfs(pq.top().second,M,V,H); pq.pop();
	ret += dfs(pq.top().second,M,V,H); pq.pop();
	return mp(ret,H);
}

ll dp[100][100][101];
pair<ll,int> C[100][100];


ll solve(int s,int e,int h) {
	if(s == e) return 0;
	if(h == 0) return 1LL << 60;
	if(getS(h) < e-s+1) return 1LL << 60;
	ll & ret = dp[s][e][h];
	if(ret != -1) return ret;
//	auto p = C[s][e];
//	if(p.second <= h) return ret = p.first;
	ret = 1LL << 60;
	ll sum = accumulate(V.begin()+s,V.begin() + e + 1,0LL);
	for(int k = s;k < e;k++)
		ret = min(ret,solve(s,k,h-1) + solve(k+1,e,h-1) + sum);
//	cout << s << " " << e << ": " << ret << endl;
	return ret;
}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	scanf("%d %d",&n,&k);
	loop(i,n) scanf("%lld",A + i);
	if(getS(k) < n) {
		puts("No solution");
		return 0;
	}
	ll b = accumulate(A,A + n,0LL);
	V = vector<ll>{A,A + n};
	sort(all(V));
//	for(int s = 0;s < n;s++)
//		for(int e = s;e < n;e++)
//			C[s][e] = huffman(s,e);
	memset(dp,-1,sizeof dp);
	ll a = solve(0,n-1,k);
	ll g = __gcd(a,b);
	a /= g;
	b /= g;
	cout << a << "/" << b << endl;
	return 0;
}
