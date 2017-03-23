#pragma GCC optimize("O3")
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

const int MAXN = 4010,MAXK = 811;
int C[MAXN][MAXN],cost[MAXN][MAXN];
int n,K;

int dp[MAXK][MAXN];

struct prob{
	int i,jleft,jright,kleft,kright;
public:
	prob(){}
	prob(int a,int b,int c,int d,int e){
		i = a;
		jleft = b; jright = c;
		kleft = d; kright = e;
	}
};

queue<prob> q;

void solve(int i,int jleft,int jright,int kleft,int kright){
	if(jleft > jright) return;	
	int jmid = (jleft + jright)/2;

	int bestk = kleft,bestval = dp[i][jmid];
	for (int k = kleft;k < jmid && k <= kright;k++){
		if(dp[i - 1][k] + cost[k + 1][jmid] < bestval){
			bestval = dp[i - 1][k] + cost[k + 1][jmid];
			bestk = k;
		}
	}

	dp[i][jmid] = bestval;
	solve(i,jleft,jmid - 1 ,kleft,bestk);
	solve(i,jmid + 1,jright,bestk,kright);
}

char buffer[MAXN << 1];
int main(){
	scanf("%d %d\n",&n,&K);
	range(i,1,n) {
		fgets(buffer,MAXN << 1,stdin);	
		int j = 1;
		for(char *token = strtok(buffer," \n");token;token = strtok(0," \n"))
			C[i][j++] = token[0] - '0';
	}
	range(i,1,n) range(j,1,n) C[i][j] += C[i][j - 1];
	for(int i = 1;i <= n;i++) {
		for(int j = 0;j < i;j++) cost[i][j] = 1 << 29;
		for(int j = i;j <= n;j++){
			cost[i][j] = (j > i) ? cost[i][j - 1] : 0;
			cost[i][j] += C[j][j] - (i ? C[j][i - 1] : 0);
		}
//		prArr(cost[i],n+1,int);
	}

	fill(&dp[0][1],&dp[K+1][0],1 << 29);
	for(int i = 1;i <= K;i++){
		solve(i,i,n,0,n);
//		prArr(dp[i],n+1,int);
	}
	cout << dp[K][n] << endl;
	cerr << dp[K][n] << endl;
	return 0;
}
