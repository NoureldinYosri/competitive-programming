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


ll A[1 << 20], B[1 << 20];
int n;

bool solve(){
	if(accumulate(A, A + n, 0LL) > accumulate(B, B + n, 0LL)) return 0;
	ll low = 0;
	ll constant = 0;
	
	loop(k, n - 1){
		int i = k%n;
		low = max(low, A[i] - B[i] - constant);		
		constant = B[i] - A[i] + constant;
		//x + constant >= 0
		low = max(low, -constant);
	}
	if(low > B[n-1]) return 0;
	ll supply = low;
	loop(i, n - 1){
//		cerr << supply << " @ " << A[i] << " " << B[i] << endl;
		ll r = max(A[i] - supply, 0LL);
		if(r > B[i]) return 0;
		supply = B[i] - r;
	}
//	cerr << supply << " + " << B[n-1] << " - " << low << " vs " << A[n-1] << endl;
	return supply + B[n-1]-low >= A[n-1];
}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	int T; scanf("%d", &T);
	while(T--){
		scanf("%d", &n);
		loop(i, n) scanf("%lld", A + i);
		loop(i, n) scanf("%lld", B + i);
		puts(solve() ? "YES" : "NO");
	}
	return 0;
}
