#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define range(i,a,b) for(int i = (a);i <= (b);i++)
#define all(A) A.begin(),A.end()
#define PI acos(-1)
#define pb push_back
#define mp make_pair
#define sz(A) ((int)A.size())
#define vi vector<int>
#define vl vector<long long>
#define vd vector<double>
#define vp vector<pair<int,int> >
#define ll long long
#define pi pair<int,int>
#define point pair<double,double>
#define pl pair<ll,ll>
#define popcnt(x) __builtin_popcount(x)
#define LSOne(x) ((x) & (-(x)))
#define xx first
#define yy second
#define PQ priority_queue
#define print(A,t) cerr << #A << ": "; copy(all(A),ostream_iterator<t>(cerr," " )); cerr << endl
#define prp(p) cerr << "(" << (p).first << " ," << (p).second << ")";
#define prArr(A,n,t)  cerr << #A << ": "; copy(A,A + n,ostream_iterator<t>(cerr," " )); cerr << endl
#define PRESTDIO() cin.tie(0),cerr.tie(0),ios_base::sync_with_stdio(0)
using namespace std;

const int MAXK = 500;
int A[30001];
int dp[30001][2*MAXK + 1];
int d;

int solve(int pos,int cur){
	if(pos > 30000) return 0;
	assert(0 <= cur - d + MAXK && cur - d + MAXK <= 2*MAXK);
	if(dp[pos][cur - d + MAXK] != -1) return dp[pos][cur - d + MAXK];
	return dp[pos][cur - d + MAXK] = A[pos] + max(max(solve(pos + cur,cur),solve(pos + cur + 1,cur + 1)),(cur > 1) ? solve(pos + cur - 1,cur - 1) : 0);
}
int main(){
	int n; scanf("%d %d",&n,&d);
	loop(i,n) {
		int x ; scanf("%d",&x);
		A[x]++;
	}
	memset(dp,-1,sizeof dp);
	cout << solve(d,d) << endl;
	
	return 0;
}
