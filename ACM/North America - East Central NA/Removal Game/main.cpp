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

int A[100],n;
int dp[100][111];

inline int gcd(int a,int b){
	if(!a) return b;
	if(!b) return a;
	return __gcd(a,b);
}

int solve(int s,int len){
	if(len <= 1) return 0;
	if(dp[s][len] != -1) return dp[s][len];
	int & ret = dp[s][len];
	ret = 1 << 29;
	for(int cut = 1;cut < len;cut++)
		ret = min(ret,solve(s,cut) + solve((s + cut)%len,len - cut));
	ret += gcd(A[s],A[(s + len)%n]);
	return ret;
}

int main(){
	#ifdef HOME
		freopen("in.in", "r", stdin);
	#endif
	while(scanf("%d",&n) == 1 && n){
		loop(i,n) scanf("%d",A + i);
		memset(dp,-1,sizeof dp);
		int ans = 1 << 30;
		for(int s = 0;s < n;s++) ans = min(ans,solve(s,n));
		cout << ans << endl;
	}
	return 0;
}
