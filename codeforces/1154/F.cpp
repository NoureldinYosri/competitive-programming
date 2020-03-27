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


const int MAXN = 2 << 10;
int A[1 << 20];
int n, m, K;
pi I[1 << 20];
vector<pi> offers;

int dp[MAXN];
int pref[MAXN];

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	scanf("%d %d %d", &n, &m, &K);
	loop(i, n) scanf("%d", A + i);
	loop(i, m) scanf("%d %d", &I[i].first, &I[i].second);
	sort(A, A + n);
	n = K;
	loop(i, m){
		if(I[i].first > n) continue;
		if(offers.empty() || offers.back().first != I[i].first) offers.pb(I[i]);
		else offers.back().second = I[i].second; 
	}
	m = sz(offers);
	assert(m <= n);
	loop(i, n) pref[i] = A[i] + (i ? pref[i-1] : 0);
	
	for(int i = 1;i <= n; i++){
		dp[i] = pref[i-1];
		loop(j, m){
			if(offers[j].first > i) continue;
			int e = i-1, s = e - (offers[j].first - offers[j].second) + 1;
			int tmp = dp[i - offers[j].first] + pref[e] - (s ? pref[s-1] : 0);
			dp[i] = min(dp[i], tmp);
		}
	}
	cout << dp[n] << endl;
	return 0;
}
