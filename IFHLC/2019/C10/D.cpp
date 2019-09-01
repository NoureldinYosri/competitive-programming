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

const int MAX = 2 << 10;
int n,P,Q;
int A[MAX];
int dp[MAX][MAX];
int nxt[2][MAX];

void computeNxt(int w,int *nxt) {
	int j = 0;
	loop(i,n){
		while(j < n && A[j] < A[i] + w) j++;
		nxt[i] = j;
	}
//	cerr << w << ": ";
//	prArr(nxt,n,int);
}

int solve(int i,int p) {
	if(i == n) return 0;
	int & ret = dp[i][p];
	if(ret != -1) return ret;
	ret = 1 + solve(nxt[1][i],p);
	if(p) ret = min(ret,solve(nxt[0][i],p-1));
//	cerr << i << " " << p << ": " << ret << endl;
	return ret;
}

bool can(int w) {
	computeNxt(w,nxt[0]);
	computeNxt(2*w,nxt[1]);
	memset(dp,-1,sizeof dp);
	return solve(0,P) <= Q;
}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	scanf("%d %d %d",&n,&P,&Q);
	P = min(n,P);
	Q = min(n,Q);
	loop(i,n) scanf("%d",A + i);
	sort(A,A + n);
	int s = 1,e = (A[n-1] - A[0] + 2)/3;
	while(s < e) {
		int m = (s + e) >> 1;
		if(can(m)) e = m;
		else s = m+1;
	}
	cout << s << endl;
	return 0;
}
#endif
