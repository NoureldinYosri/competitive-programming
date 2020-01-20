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


ll S;
ll A;
int n;
ll B;

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	int T; scanf("%d",&T);
	while(T--){
		S = A = 0;
		scanf("%d",&n);
		loop(i,n){
			scanf("%lld",&B);
			S += B;
			A ^= B;
		}
		A <<= 1;
		
		if(S == A){
			puts("0");
			continue;
		}
		else {
			puts("1");
			int i = 0;
			ll x = 0;
			while(S != A){
				int b1 = S & 1;
				int b2 = A & 1;
				if(b1 != b2){
					x |= 1LL << i;
					S ++;
					A ^= 2;
				}
				i++;
				S >>= 1;
				A >>= 1;
			}
			printf("%lld\n",x);
		}
	}
	return 0;
}
