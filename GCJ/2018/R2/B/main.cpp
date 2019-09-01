#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define range(i,a,b) for(int i = (a);i <= (b);i++)
#define all(A) A.begin(),A.end()
#define pb push_back
#define mp make_pair
#define sz(A) ((int)A.size())
#define vi vector<int>
#define vd vector<double>
#define vp vector<pair<int,int> >
#define ll long long
#define pi pair<int,int>
#define popcnt(x) __builtin_popcountll(x)
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
using namespace std;


int dp[501][501][501];

int solve(int r,int R,int B){
	int & ret = dp[r][R][B];
	if(ret != -1) return ret;
	ret = 0;
	int s = 0,rR = R,rB = B;
	for(int c = 0;r <= rR && s <= rB;s++){
		rR -= r;
		rB -= s;
		c += r || s;
		ret = max(ret,c + solve(r+1,rR,rB));
	}

	return ret;
}


int main(int argc,char **argv){
#ifdef HOME
	freopen("in.in","r",stdin);
#endif
	int T; scanf("%d",&T);
	memset(dp,-1,sizeof dp);
	range(t,1,T) {
		int R,B; scanf("%d %d",&R,&B);
		printf("Case #%d: %d\n",t,solve(0,R,B));
	}
	return 0;
}