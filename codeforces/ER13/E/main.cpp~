#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0,_ = (n);i < _;i++)
#define range(i,a,b) for(int i = (a),_ = (b);i <= _;i++)
#define rrep(i,n) for(int i = (n);i >= 0;i--)
#define rran(i,a,b) for(int i = (b),_ = (a);i >= _;i--)
#define all(A) A.begin(),A.end()
#define PI acos(-1)
#define pb push_back
#define mp make_pair
#define sz(A) A.size()
#define vi vector<int>
#define vl vector<long>
#define vd vector<double>
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

double dp[18][1 << 18],dp2[18][1 << 18];
int n;
double G[18][18];

double solve(int p,int msk){
	if(!msk) return 1;
	if(dp[p][msk] != -1) return dp[p][msk];
	dp[p][msk] = 0; int ctr = 0;
	loop(i,n){
		if(msk & (1 << i)){
			ctr++;
			dp[p][msk] += solve(p,msk ^ (1 << i))*G[p][i];
		}
	}
	dp[p][msk] /= ctr;
	return dp[p][msk];
}

double solve2(int i,int tot){
	if(!tot) return 1;
	if(dp2[i][tot] != -1) return dp2[i][tot];		
	double p = 0; int ctr = 0;
	loop(j,n){
		bool c = tot & (1 << j); 
		if(!c) continue;
		loop(msk,1 << n){			
			if(msk & (1 << j)) continue;
			if((msk & tot) != msk) continue;			
			ctr ++;
			int cmp = tot ^ msk ^ (1 << j);
			p += solve2(j,msk)*solve(i,cmp)*G[i][j];
		}
	}
	p /= ctr;
	return dp2[i][tot] = p;	
}


int main(){
	fill(&dp[0][0],&dp[18][0],-1);
	fill(&dp2[0][0],&dp2[18][0],-1);
	scanf("%d",&n);
	if(n == 1){
		puts("1");
		return 0;
	}	
	int tot = (1 << n) - 1;
	loop(i,n) loop(j,n) scanf("%lf",&G[i][j]);
	double ans = solve2(0,((1 << n) - 1)^1);
	printf("%.15f\n",ans);
	cerr << ans << endl;
	return 0;
}
