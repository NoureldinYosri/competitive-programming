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

int dp[10001][1001],m,n;
char s1[20000],s2[2000];
int pf[1001];
int dp2[256][1001];

const int INF = 1 << 29;

int GetLen(char c,int l){
	if(dp2[c][l] != -1) return dp2[c][l];
	int & ans = dp2[c][l];	
	while(l && s2[l] != c) l = pf[l - 1];
	if(s2[l] == c) l++;
	return ans = l;
}

void BuildFailure(){
	pf[0] = 0;
	range(i,1,n - 1) pf[i] = GetLen(s2[i],pf[i - 1]);
}

int solve(int i,int l){
	if(l == n) return INF;
	if(i == m) return 0;
	if(dp[i][l] != -1) return dp[i][l];
	return dp[i][l] = min(solve(i + 1,l) + 1,solve(i + 1,GetLen(s1[i],l))); 
}

int main(){
	while(scanf("%s %s",s1,s2) == 2){
		m = strlen(s1);
		n = strlen(s2);
		fill(&dp[0][0],&dp[m][0],-1);
		fill(&dp2[0][0],&dp2[256][0],-1);
		BuildFailure();
		printf("%d\n",solve(0,0));
	}
	return 0;	
}
