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


int A[1 << 20], n, m;
int W[1 << 20];

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	int T; scanf("%d", &T);
	while(T--){
		scanf("%d %d", &n, &m);
		loop(i, n) scanf("%d", A + i);
		loop(i, m) scanf("%d", W + i);
		sort(A, A + n);
		sort(W, W + m);
		reverse(W, W + m);
		int ones = 0;
		while(m && W[m-1] == 1){
			ones++;
			m--;
		}
		int s = 0, e = n-1;
		ll ans = 0;
		while(ones){
			ans += 2*A[e--];
			ones--;
		}
//		prArr(A, e+1, int);
//		prArr(W, m, int);
		loop(i, m){
			int k = W[i];
			if(k == 1){
				ans += 2*A[e--];
			} else {
				ans += A[s] + A[e];
				e--;
				s += k - 1;
			}
		}
		printf("%lld\n", ans);
	}
	return 0;
}
