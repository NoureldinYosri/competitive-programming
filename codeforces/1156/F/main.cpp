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

const int mod = 998244353,MAX = 5003;
int A[MAX],n;
int f[MAX],m;
int inv[MAX];

int add(int a,int b) {
	a += b;
	if(a >= mod) a -= mod;
	return a;
}
int mul(int a,int b){
	return (a*(ll)b)%mod;
}
int fastPower(int a,int p) {
	if(p == 0) return 1;
	int b = 1;
	for(;p > 1;p >>= 1) {
		if(p & 1) b = mul(a,b);
		a = mul(a,a);
	}
	return mul(a,b);
}

int dp[MAX][MAX][2];

int solve(int cur,int len,int is_end) {
	if(cur == m) return 0;
	int & ret = dp[cur][len][is_end];
	if(ret != -1) return ret;
	ret = 0;
	if(is_end) ret = mul(f[cur]-1,inv[n-len]);
	ret = add(ret,solve(cur+1,len,0));
	if(!is_end) {
		int p = mul(f[cur],inv[n-len]);
		ret = add(ret,mul(p,solve(cur,len+1,1)));
	}
	return ret;
}


//int solve(){
//	for(int cur = m-1;cur >= 0;cur--)
//		for(int len = n;len >= 0;len--)
//			for(int is_end = 1;is_end >= 0;is_end--) {
//				int & ret = dp[cur][len][is_end];
//
//			}
//	return dp[0][0][0];
//}
//
int main(int argc,char **argv){
#ifdef HOME
	freopen("in.in","r",stdin);
#endif
	scanf("%d",&n);
	loop(i,n) scanf("%d",A + i);
	sort(A,A + n);
	for(int i = 0;i < n;) {
		int j = i;
		while(j < n && A[i] == A[j]) j ++;
		f[m++] = j-i;
		i = j;
	}
	inv[1] = 1;
	for(int i = 2;i <= n;i++){
		inv[i] = mod-mul(mod/i,inv[mod%i]);
		assert(mul(i,inv[i]) == 1);
	}
	memset(dp,-1,sizeof dp);
	printf("%d\n",solve(0,0,0));
//	cout << solve() << endl;
	return 0;
}
