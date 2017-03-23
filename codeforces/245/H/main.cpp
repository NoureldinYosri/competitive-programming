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

const int MAX = 5010;
char line[MAX];
int dp[MAX][MAX][2];

void solve(int s,int e){
	if(s == e){
		dp[s][e][0] = dp[s][e][1] = 1;
		return;
	}
	if(e == s + 1){
		solve(s+1,e);
		solve(s,e-1);
		dp[s][e][0] = 0;
		dp[s][e][1] = 2;
		if(line[s] == line[e]){
			dp[s][e][0] = 1;
			dp[s][e][1] = 3;
		}
		return;
	}
	if(dp[s][e][0] != -1) return;
	solve(s+1,e);
	solve(s,e-1);
	solve(s+1,e-1);
	dp[s][e][0] = 0;
	dp[s][e][1] = dp[s+1][e][1] + dp[s][e-1][1] - dp[s + 1][e - 1][1];
	if(line[s] == line[e] && dp[s + 1][e - 1][0] ){
		dp[s][e][0] = 1;
		dp[s][e][1] ++;
	}
}

int main(){
	memset(dp,-1,sizeof dp);
	scanf("%s",line);
	solve(0,int(strlen(line))-1);	
	int n; scanf("%d",&n);
	loop(i,n){
		int l,r; scanf("%d %d",&l,&r); l--,r--;
		printf("%d\n",dp[l][r][1]);
	//	cerr << dp[l][r][1]  << endl;
	}
	
	return 0;
}
