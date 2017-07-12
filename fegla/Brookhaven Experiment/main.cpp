#pragma GCC optimize ("O3")
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
#define pl pair<ll,ll>
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
const double PI = acos(-1);
using namespace std;

double dp[1000][1000];
int n,m,L;
double P[1024];
int damage[1024];

double solve(int i,int l){
	if(i == n) return n;
	double & ret = dp[i][l];
	if(ret == ret) return ret;
	ret = P[i]*solve(i+1,l);
	if(damage[i] >= l) {
		if(i+1 >= m)
			ret += (1 - P[i]) * (i + 1);
	}
	else ret += (1 - P[i]) * solve(i+1,l - damage[i]);
	return ret;
}

int main(){
	freopen("brookhaven.in", "r", stdin);
	int T; scanf("%d",&T);
	while(T--) {
		scanf("%d %d %d",&n,&L,&m);
		loop(i,n) scanf("%lf",P + i);
		loop(i,n) scanf("%d",damage + i);

		memset(dp,-1,sizeof dp);
		printf("%.9f\n",solve(0,L));
	}
	return 0;
}
