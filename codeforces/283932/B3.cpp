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


int n, K;
int A[1 << 20];
int dp[1 << 20];
ll pref[1 << 20];

bool f(ll target){
	int j = n;
	multiset<int> MS;
	MS.insert(0);
	for(int i = n; i; i--){
		while(pref[j] - pref[i-1] > target) {
			MS.erase(MS.find(dp[j + 1]));
			j--;
		}
		dp[i] = 1 + *MS.begin();
		MS.insert(dp[i]);
	}
//	prArr(dp + 1, n, int);
	return dp[1] <= K;
}



int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	scanf("%d %d", &n, &K);
	for(int i = 1; i <= n; i++) {
		scanf("%d", A + i);
		pref[i] = pref[i-1] + A[i];
	}
	ll s = *max_element(A + 1, A + n + 1), e = accumulate(A + 1, A + n + 1, 0LL);
	while(s < e){
		ll m = s + (e-s)/2;
		if(f(m)) e = m;
		else s = m+1;
	}
	cout << s << endl;

	return 0;
}
