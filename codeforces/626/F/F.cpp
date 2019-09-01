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

const int mod = 1e9 + 7;
const int MAXN = 211,MAXK = 1024;
int A[MAXN],n,m;
int dp[MAXN][MAXN][MAXK];

int add(int a,int b) {
	a += b;
	if(a >= mod) a -= mod;
	return a;
}
int mul(int a,int b){
	return (a*(ll)b)%mod;
}

int solve(int i,int c,int k) {
	if(k < 0 || c < 0) return 0;
	if(i == n-1) return c <= 1;
	int & ret = dp[i][c][k];
	if(ret != -1) return ret;
	ret = 0;
	int diff = A[i + 1] - A[i];
	ret = add(ret,mul(c,solve(i+1,c,k - c*diff)));
	ret = add(ret,mul(c,solve(i+1,c-1,k - (c-1)*diff)));
	ret = add(ret,solve(i+1,c+1,k-(c+1)*diff));
	ret = add(ret,solve(i+1,c,k-c*diff));
	return ret;
}



int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	scanf("%d %d",&n,&m);
	loop(i,n) scanf("%d",A + i);
	sort(A,A + n);
	memset(dp,-1,sizeof dp);
	printf("%d\n",solve(0,0,m));
	return 0;
}
