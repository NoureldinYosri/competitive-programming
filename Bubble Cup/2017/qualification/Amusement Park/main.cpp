#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define range(i,a,b) for(int i = (a);i <= (b);i++)
#define all(A) A.begin(),A.end()
#define pb push_back
#define mp make_pair
#define sz(A) ((int)A.size())
#define vi vector<int>
#define vl vector<long long>
#define vd vector<double>
#define vp vector<pair<int,int> >
#define ll long long
#define pi pair<int,int>
#define popcnt(x) __builtin_popcount(x)
#define LSOne(x) ((x) & (-(x)))
#define xx first
#define yy second
#define PQ priority_queue
#define print(A,t) cerr << #A << ": "; copy(all(A),ostream_iterator<t>(cerr," " )); cerr << endl
#define prp(p) cerr << "(" << (p).first << " ," << (p).second << ")";
#define prArr(A,n,t)  cerr << #A << ": "; copy(A,A + n,ostream_iterator<t>(cerr," " )); cerr << endl
#define PRESTDIO() cin.tie(0),cerr.tie(0),ios_base::sync_with_stdio(0)
#define what_is(x) cerr << #x << " is " << x << endl
#define bit_lg(x) (assert(x > 0),__builtin_ffsll(x) - 1)
const double PI = acos(-1);
using namespace std;

const int oo = 1 << 29;
const int MAX = 2000;
int dp[MAX][MAX];
int cost[MAX][MAX],C[MAX][MAX];
int n,K;


void solve(int ileft,int iright,int kleft,int kright,int tK){
	if(iright < ileft) return;
	int m = (ileft + iright) >> 1;
	int bestK = kleft;
	dp[tK][m] = oo;
	for(int k = kleft;k <= kright && k < m;k++){
		int t = dp[tK - 1][k] + cost[k + 1][m];
		if(t < dp[tK][m]){
			bestK = k;
			dp[tK][m] = t;
		}
	}
	solve(ileft,m - 1,kleft,bestK,tK);
	solve(m + 1,iright,bestK,kright,tK);
}
int main(){
	//freopen("logger.out","w",stderr);
/*	#ifndef ONLINE_JUDGE
		freopen("input.in", "r", stdin);
		freopen("output.out", "w", stdout);
	#endif
*/	scanf("%d %d",&n,&K);
	range(i,1,n) range(j,1,n) {
		scanf("%d",&C[i][j]);
		C[i][j] += C[i][j - 1];
	}
	range(i,1,n) {
		range(j,1,i-1) cost[i][j] = oo;
		range(j,i+1,n) cost[i][j] = cost[i][j - 1] + C[j][j] - C[j][i - 1];
	}
	fill(dp[0],dp[1],oo);
	dp[0][0] = 0;
	range(k,1,K) {
		solve(0,n,0,n,k);
	}
	cout << dp[K][n] << endl;
	return 0;
}
