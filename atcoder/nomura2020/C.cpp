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

int n;
int A[1 << 20];

ll H[1 << 20];



int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	scanf("%d", &n);
	loop(i, n+1) scanf("%d", A + i);
	
	H[n] = 0;
	for(int i = n; i > 0; i--)
		H[i-1] = H[i] + A[i];
	
	ll high = 1;
	loop(i, n+1){
		if(A[i] > high){
			cout << "-1" << endl;
			return 0;
		}
		high -= A[i];
		high = H[i] = min(H[i], high);
		high <<= 1;
	}
	
	loop(i, n) {
		ll low = H[i], high = low << 1;
		ll x = A[i+1] + H[i+1];
		assert(low <= x && x <= high);
	}

	ll ans = 0;
//	prArr(H, n+1, ll);
//	prArr(A, n+1, int);
	loop(i, n+1) ans += H[i] + A[i];
	cout << ans << endl;
	
	return 0;
}
