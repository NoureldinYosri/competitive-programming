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

const int MAXN = 100*1000 + 10, MAXZ = 5;
int A[MAXN];
int n, K, Z;
int dp[MAXN][MAXZ + 1][2], visNum;
int visID[MAXN][MAXZ+1][2];

int solve(int steps, int z, bool wasLeft){
	if(steps == K) return 0;
	int & ret = dp[steps][z][wasLeft];
	if(visID[steps][z][wasLeft] == visNum) return ret;
	visID[steps][z][wasLeft] = visNum;
	int cur = steps - 2*z;
	ret = 0;
	if(cur+1 < n) ret = max(ret, solve(steps+1, z, 0) + A[cur+1]);
	if(cur && z < Z && !wasLeft) ret = max(ret, solve(steps + 1, z + 1, 1) + A[cur-1]);
	return ret;
}


int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	int T; scanf("%d", &T);
	while(T--){
		scanf("%d %d %d", &n, &K, &Z);
		loop(i, n) scanf("%d", A + i);
		visNum++;
		printf("%d\n", solve(0, 0, 0) + A[0]);
	}
	return 0;
}
