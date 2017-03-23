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

char buffer[50];
double dp[21][10000*2 + 10][21];

double solve(int n,int t,int y){
	if(t < 0) return 0;
	if(n == 0) return t == 0;
	assert(n <= 20 && t < 10000*2 + 10 && y <= 20);
	double & ret = dp[n][t][y];
	if(ret == ret) return ret;
	ret = 0;
	range(i,1,y) ret += solve(n-1,t - i,y);
	ret /= y;
	return ret;
}

void parse(int & x,int & y,int & z){
	int sgn = 1,ctr = 0; char *l = buffer; z = 0;
	for(char *p = buffer;*p;p++) {
		if(*p == '-') sgn = -1;	
		if(*p == '-' || *p == '+' || *p == 'd'){
			*p = 0;
			if(!ctr) sscanf(l,"%d",&x);
			else if(ctr == 1) sscanf(l,"%d",&y);
			else sscanf(l,"%d",&z);
			ctr++; l = p + 1;
		}
	}
	if(ctr == 1) sscanf(l,"%d",&y);
	else sscanf(l,"%d",&z);
	z *= sgn;
}		

int main(){
	memset(dp,-1,sizeof dp);
	int T; scanf("%d",&T);
	loop(t,T){
		int H,S; scanf("%d %d",&H,&S);
		double ans = 0.0;
		loop(i,S){
			scanf("%s",buffer);
			int x,y,z; parse(x,y,z);
			double t = 0.0;
			range(i,1,x*y) if(i + z >= H) t += solve(x,i,y);
			ans = max(ans,t);
		}	
		printf("Case #%d: %.6f\n",t+1,max(ans,0.0));
	}		
	return 0;
}
