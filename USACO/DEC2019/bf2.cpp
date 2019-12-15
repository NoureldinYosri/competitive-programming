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

const int MAXN = 50,MAXM = 20;
int n,m;
int W[MAXN];
int ord[MAXN];
int L[MAXN],R[MAXN],content[MAXN];

int dp[MAXN][1 << MAXM][2];

int solve(int cur,int msk,bool used){
	if(cur == -1) return used ? solve(n-1,msk,0) : 0;
	int & ret = dp[cur][msk][used];
	if(ret != -1) return ret;
	ret = solve(cur-1,msk,used);
	if(msk & content[cur]) ret = max(ret,solve(cur-1,msk & ~content[cur],1) + W[cur]);
	return ret;
}

int main(){
#ifdef HOME
	freopen("in.in","r",stdin);
#else
	freopen("pieaters.in", "r", stdin);
	freopen("pieaters.out", "w", stdout);
#endif
	scanf("%d %d",&n,&m);
	loop(i,n) {
		scanf("%d %d %d",W + i,L + i,R + i);
		L[i]--,R[i]--;
		content[i] = (2 << R[i]) - 1;
		content[i] ^= (1 << L[i]) - 1;
//		cout << L[i] << " " << R[i] << " " << content[i] << endl;
	}
	memset(dp,-1,sizeof dp);
	cout << solve(n-1,(1 << n) - 1,0) << endl;
	return 0;
}
