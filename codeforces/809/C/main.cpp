#pragma GCC optimize ("O3")
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
#define pl pair<ll,ll>
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
const double PI = acos(-1);
using namespace std;

const int mod = 1e9 + 7;
int dp[31][2][2][2];
int cnt[31][2][2][2];
int X,Y,K;

int add(int x,int y){
	x += y;
	if(x >= mod) x -= mod;
	if(x < 0) x += mod;
	return x;
}

int mul(int x,int y){
	return (x*1LL*y)%mod;
}

bool check_bit(int x,int i){
	return x & (1 << i);
}
int solve(int bit,bool equalX,bool equalY,bool equalZ){
	if(bit == 31) return 1;
	if(cnt[bit][equalX][equalY][equalZ] != -1) return cnt[bit][equalX][equalY][equalZ];
	int & ret = cnt[bit][equalX][equalY][equalZ]; ret = 0;
	for(int b1 = 0;b1 < 2;b1++)
		for(int b2 = 0;b2 < 2;b2++) {
			bool can = 1;
			if(equalX && b1 && !check_bit(X,30-bit)) can = 0;
			if(equalY && b2 && !check_bit(Y,30-bit)) can = 0;
			if(equalZ && (b1^b2) && !check_bit(K,30-bit)) can = 0;
			if(!can) continue;
			bool nequalX = equalX && (b1 == check_bit(X,30-bit));
			bool nequalY = equalY && (b2 == check_bit(Y,30-bit));
			bool nequalZ = equalZ && ((b1^b2) == check_bit(K,30-bit));
			ret = add(ret,solve(bit+1,nequalX,nequalY,nequalZ));
		}
	return ret;
}
int solve2(int bit,bool equalX,bool equalY,bool equalZ){
	if(bit == 31) return 1;
	if(dp[bit][equalX][equalY][equalZ] != -1) return dp[bit][equalX][equalY][equalZ];
	int & ret = dp[bit][equalX][equalY][equalZ]; ret = 0;
	for(int b1 = 0;b1 < 2;b1++)
		for(int b2 = 0;b2 < 2;b2++) {
			bool can = 1;
			if(equalX && b1 && !check_bit(X,30-bit)) can = 0;
			if(equalY && b2 && !check_bit(Y,30-bit)) can = 0;
			if(equalZ && (b1^b2) && !check_bit(K,30-bit)) can = 0;
			if(!can) continue;
			bool nequalX = equalX && (b1 == check_bit(X,30-bit));
			bool nequalY = equalY && (b2 == check_bit(Y,30-bit));
			bool nequalZ = equalZ && ((b1^b2) == check_bit(K,30-bit));
			ret = add(ret,solve2(bit+1,nequalX,nequalY,nequalZ));
			ret = add(ret,mul(((b1^b2) << (30-bit)),solve(bit+1,nequalX,nequalY,nequalZ)));
		}
	return ret;
}

int solve(int x,int y,int k){
	memset(dp,-1,sizeof dp);
	memset(cnt,-1,sizeof cnt);
	X = x,Y = y,K = k;
//	cerr << solve(0,1,1,1) << " " << solve2(0,1,1,1) << endl;
	return solve2(0,1,1,1);
}

int main(){
	#ifndef ONLINE_JUDGE
		freopen("in.in", "r", stdin);
	#endif
	int q; scanf("%d",&q);
	while(q--){
		int x1,y1,x2,y2,k;
		scanf("%d %d",&x1,&y1); x1--,y1--;
		scanf("%d %d",&x2,&y2); x2--,y2--;
		scanf("%d",&k); k--;
		int ans = solve(x2,y2,k);
		if(x1) ans = add(ans,-solve(x1-1,y2,k));
		if(y1) ans = add(ans,-solve(x2,y1-1,k));
		if(x1 && y1) ans = add(ans,solve(x1-1,y1-1,k));
		printf("%d\n",ans);
	}
	return 0;
}
