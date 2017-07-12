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
#define popcnt(x) __builtin_popcount(x)
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

double P[18][18];
int n;
double dp[18][1 << 18];
double solve(int cur,int msk){
	if(!msk) return cur == 0;
	double & ret = dp[cur][msk];
	if(ret == ret) return ret;
	ret = 0;
	int ctr = 0;
	loop(i,n) if(msk & (1 << i)){
		ret = max(ret,P[i][cur] * solve(i,msk ^ (1 << i)) + P[cur][i] * solve(cur,msk ^ (1 << i)));
		++ctr;
	}
//	ret /= ctr;
	return ret;
}

int main(){
	#ifndef ONLINE_JUDGE
		freopen("input.in", "r", stdin);
		freopen("output.out", "w", stdout);
	#endif
	scanf("%d",&n);
	loop(i,n) loop(j,n) scanf("%lf",&P[i][j]);
	memset(dp,-1,sizeof dp);
	double ans = 0; int tot = (1 << n) - 1;
	loop(i,n) {
		double t = solve(i,tot ^ (1 << i));
		ans = max(ans,t);
	}
	printf("%.10f\n",ans);
	fprintf(stderr,"%.10f\n",ans);
	return 0;
}
