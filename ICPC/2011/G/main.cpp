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

const double EPS = 1e-9;
int n;
int L[500];
double dp[500][500];

double get_theta(double R,int len){
	double diff = (2*R*R - len*len)/(2.0*R*R);
	if(abs(diff) > 1) return 3*PI;
	double t = acos(diff);
	assert(t >= 0);
	return t;
}

double get_theta(double R,int S,int E){
	double theta = 0;
	for(int i = S;i <= E;i++) theta += get_theta(R,L[i]);
	return theta;
}

double get_radius(int S,int E){
	double s = 0,e = 1e6;
	for(int i = 0;i < 1000 && e - s > EPS/10;i++){
		double m = s + (e - s)/2;
		if(get_theta(m,S,E) <= 2*PI) e = m;
		else s = m;
	}
	return s;
}



double polygon_area(int S,int E){
	double ret = 0;
	double t = 0;
	double R = get_radius(S,E);
	for(int i = S;i <= E;i++) {
		ret += 0.5*R*R*abs(sin(get_theta(R,L[i])));
		t += get_theta(R,L[i]);
	}
	if(abs(t - 2*PI) > EPS) ret = 0;
	return ret;
}


double solve(int s,int e){
	if(e - s + 1 < 3) return 0;
	double ret = dp[s][e] ;
	if(ret == ret) return ret;
	ret = polygon_area(s,e);
	for(int k = s + 1;k < e;k++)
		ret = max(ret,solve(s,k - 1) + solve(k + 1,e));
	return ret;
}

int main(){
	freopen("logger.out","w",stderr);
	#ifndef ONLINE_JUDGE
		freopen("input.in", "r", stdin);
		freopen("output.out", "w", stdout);
	#endif
	for(int t = 1;scanf("%d",&n) == 1 && n;t++){
		loop(i,n) scanf("%d",L + i);
		memset(dp,-1,sizeof dp);
		printf("Case %d: %.6lf\n",t,solve(0,n-1));
	}
	return 0;
}
