#ifdef ACTIVE
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

const int MAX = 1024;
int n;
int M[MAX][MAX];
int G[MAX],A[MAX];

vi getDivisors(int x) {
	vi ret;
	for(int i = 1;i*i <= x;i++) if(x%i == 0) {
		ret.push_back(i);
		if(i != x/i) ret.push_back(x/i);
	}
	return ret;
}

bool valid(int a) {
	A[0] = a;
	for(int i = 1;i < n;i++) {
		assert(M[0][i]%a == 0);
		int ai = M[0][i]/a;
		if(G[i]%ai) return 0;
		A[i] = M[0][i]/a;
		loop(j,i) if(M[j][i] != A[i]*(ll)A[j]) return 0;
	}
	return 1;
}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	scanf("%d",&n);
	loop(i,n) loop(j,n) scanf("%d",&M[i][j]);
	loop(i,n) {
		int g = 0;
		loop(j,n) if(i != j) g = __gcd(g,M[i][j]);
		G[i] = g;
	}
	for(int a : getDivisors(G[0]))
		if(valid(a)){
			loop(i,n) printf("%d ",A[i]);
//			loop(i,n) loop(j,n) if(i != j) assert(M[i][j] == A[i]*(ll)A[j]);
			return 0;
		}
	return 0;
}
#endif
