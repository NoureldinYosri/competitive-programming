#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define range(i,a,b) for(int i = (a);i <= (b);i++)
#define rrep(i,n) for(int i = (n);i >= 0;i--)
#define rran(i,a,b) for(int i = (b);i >= (a);i--)
#define step(i,a,b,d) for(int i = (a);i <= (b); i += d)
#define all(A) A.begin(),A.end()
#define PI acos(-1)
#define pb push_back
#define mp make_pair
#define sz(A) A.size()
#define len(A) A.length()
#define vi vector<int>
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
#define pre() cin.tie(0),cerr.tie(0),ios_base::sync_with_stdio(0)
using namespace std;

char line[100];
int dp[101][101],n;
char Z[][3] = {"()","[]"};

int solve(int s,int e){
	if(s == e) return 1 << 29;
	if(s > e) return 0;
	if(dp[s][e] != -1) return dp[s][e];
	dp[s][e] = 1 << 29;	
	loop(i,2) dp[s][e] = min(dp[s][e],solve(s + 1,e - 1) + (line[s] != Z[i][0]) + (line[e] != Z[i][1])); 
	range(j,s + 1,e - 1) dp[s][e] = min(dp[s][e],solve(s,j) + solve(j + 1,e));
	return dp[s][e];
}

int main(){
	int T;
	scanf("%d",&T);
	while(T--){
		scanf("%s",line);
		n = strlen(line);
		loop(i,n) loop(j,n) dp[i][j] = -1;
		int ans = solve(0,n - 1);
		if(ans == (1 << 29)) ans = -1;
		printf("%d\n",ans);	
	}
	return 0;
}
