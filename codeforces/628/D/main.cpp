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

const int MAX = 2000 + 10,mod = 1e9 + 7;
int m,td;
char A[MAX],B[MAX];
int n;
int dp[MAX][MAX][2][2];

int add(int a,int b,int c) {
	a += b;
	return a%c;
}
int mul(int a,int b,int c) {
	return (a*(ll)b)%c;
}


int solve(int i,int r,int equalA,int equalB) {
	if(i == n) return r == 0;
	int & ret = dp[i][r][equalA][equalB];
	if(ret != -1) return ret;
	ret = 0;
	int a = A[i] - '0',b = B[i] - '0';
	int lo = equalA ? a : 0;
	int hi = equalB ? b : 9;
	for(int d = lo;d <= hi;d++) {
		if(i%2 && d != td) continue;
		if(!(i%2) && d == td) continue;
		int nr = add(mul(r,10,m),d,m);
		int tmp = solve(i+1,nr,equalA&&(d==a),equalB&&(d==b));
		ret = add(ret,tmp,mod);
	}
	return ret;
}


int main(int argc,char **argv){
#ifdef HOME
	freopen("in.in","r",stdin);
#endif
	scanf("%d %d %s %s",&m,&td,A,B);
	n = strlen(A);
	assert(strlen(A) == strlen(B));
	memset(dp,-1,sizeof dp);
	cout << solve(0,0,1,1) << endl;
	return 0;
}
