/*#pragma GCC optimize ("O3")
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
int dp[50][50][51][51];
int deg[50],n;
int C[100][100];
int memo[100][100][100];
int cnt[2][100];

int add(int x,int y){
	x += y;
	if(x >= mod) x -= mod;
	return x;
}

int sub(int x,int y){
	x = add(x,-y);
	if(x < 0) x += mod;
	return x;
}

int mul(int x,int y){
	return (x*1LL*y)%mod;
}
void init(){
	memset(memo,-1,sizeof memo);
	memset(dp,-1,sizeof dp);
	loop(i,100) {
		C[i][0] = C[i][i] = 1;
		range(j,1,i-1) C[i][j] = add(C[i - 1][j],C[i - 1][j - 1]);
	}
}

int graphsOfOnesAndTwos(int c1,int c2,int r = 0){
	if(c1 < 0 || c2 < 0 || c < 0) return 0;
	if(!c1 && !c2 && !r) return 1;
	if(memo[c1][c2][r] != -1) return memo[c1][c2][r];
	int & ret = memo[c1][c2][r];
	ret = 0;
	ret = add(ret,mul(C[c1][2],graphsOfOnesAndTwos(c1-2,c2,r)));
	ret = add(ret,mul(C[c2][2],graphsOfOnesAndTwos(c1,c2-2,r+1)));
	ret = add(ret,mul(mul(c1,c2),graphsOfOnesAndTwos(c1,c2-1,r)));
	return ret;
}


void get_cnt(int s,int e,int & ones,int & twos){
	ones = cnt[0][e] - cnt[0][s];
	twos = cnt[1][e] - cnt[1][s];
}

int solve(int st,int cur,int c1,int c2){
	if(c1 < 0 || c2 < 0) return 0;
	int c11,c22; get_cnt(st,cur,c11,c22);
	if(cur == n) return mul(graphsOfOnesAndTwos(c1,c2),graphsOfOnesAndTwos(c11,c22));
	int & ret = dp[st][cur][c1][c2];
	if(ret != -1) return ret;
	ret = 0;
	if(c11 || c22) ret = add(ret,mul(graphsOfOnesAndTwos(c1,c2) , solve(cur,cur+1,c11,c22)));
	ret = add(ret,mul(c1,solve(st,cur+1,c1-1,c2)));
	ret = add(ret,mul(c2,solve(st,cur+1,c1+1,c2-1)));
	cerr << st << " " << cur << " " << c1 << " " << c2 << " " << c11 << " " << c22 << " -> " << ret << endl;
	return ret;
}

int main(){
	#ifndef ONLINE_JUDGE
		freopen("in.in", "r", stdin);
	#endif
	init();
	cin >> n;
	loop(i,n) cin >> deg[i];
	if(n-1 < deg[0]) {
		puts("0");
		return 0;
	}
	if(n == 1) puts((deg[0] == 0) ? "1" : "0");
	else if(n == 2){
		if(deg[0] == 1 && deg[1] == 1) puts("1");
		else puts("0");
	}
	else {
		range(i,1,n-1){
			cnt[0][i + 1] = cnt[0][i] + (deg[i] == 2);
			cnt[1][i + 1] = cnt[1][i] + (deg[i] == 3);
		}
		cout << solve(deg[0] + 1,deg[0] + 1,cnt[0][deg[0]+1],cnt[1][deg[0]+1]) << endl;
	}
	return 0;
}*/
