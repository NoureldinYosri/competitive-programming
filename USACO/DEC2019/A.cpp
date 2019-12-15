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

const int MAXN = 50,MAXM = (MAXN*(MAXN + 1))/2 + 1;
int n,m;
int W[MAXN];
int L[MAXN],R[MAXN];
vi who[MAXM];
int dp[MAXM];

int solve(int x){
	if(x == m) return 0;
	int & ret = dp[x];
	if(ret != -1) return ret;
	ret = 0;
	for(int i : who[x])
		ret = max(ret,W[i]);
	ret += solve(x+1);
	return ret;
}


int main(){
#ifdef HOME
	freopen("in.in","r",stdin);
#else
//	freopen("pieaters.in", "r", stdin);
//	freopen("pieaters.out", "w", stdout);
#endif
	scanf("%d %d",&n,&m);
	loop(i,n) {
		scanf("%d %d %d",W + i,L + i,R + i);
		L[i]--,R[i]--;
		who[L[i]].push_back(i);
	}
	memset(dp,-1,sizeof dp);
	cout << solve(0) << endl;
	return 0;
}
