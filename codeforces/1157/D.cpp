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


ll A[1 << 20];


int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	ll n, k; cin >> n >> k;
	
	if(n < k*(k+1)/2) {
		cout << "NO" << endl;
		return 0;
	}
	ll low = 1, high = n;
	loop(i, k){
		ll r = k - i;
		//w * r + r*(r-1)/2 <= n
		ll n0 = (r*(r-1)/2);
		ll w = (n - n0)/r;
		w = max(w, low);
		w = min(w, high);
		n -= w;
		if(n < 0){
			puts("NO");
			return 0;
		}
		A[i] = w;
		low = w+1;
		high = 2*w;		
	}
	if(n){
		puts("NO");
		return 0;
	}
	puts("YES");
	loop(i, k)printf("%lld%c", A[i], " \n"[i==k-1]);
	
	return 0;
}
