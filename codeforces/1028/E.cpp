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

const int MAX = 1 << 20;
ll B[MAX],A[MAX];
int n;


int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	scanf("%d",&n);
	loop(i,n) scanf("%lld",B + i);
	int c = min_element(B,B + n) - B;
	loop(i,n) if(B[c] == B[i] && B[(i+1)%n] > B[(c+1)%n]) c = i;
	A[c] = B[c] + 187127*B[(c+1)%n];
	bool done = 0;
	if(!A[c]) {
		done = 1;
		fill(A,A + n,1LL);
	}
	for(int t = 0,i = c;t < n-1 && !done;t++){
		int nxt = i;
		i = (i+n-1)%n;
		int prv = (i+n-1)%n;
		if(t == n-2) {
			A[i] = B[i];
			break;
		}
		//k*A[nxt] + B[i] > B[prv]
		int b = max(0LL,B[prv] - B[i]);
		ll k = b / A[nxt] + 1;
		A[i] = k*A[nxt] + B[i];
	}
//	prArr(A,n,ll);
	bool cond = 1;
	loop(i,n) cond &= A[i]%A[(i+1)%n] == B[i];
	puts(cond ? "YES" : "NO");
	if(cond) {
		loop(i,n) printf("%lld%c",A[i]," \n"[i==n-1]);
	}
	return 0;
}
