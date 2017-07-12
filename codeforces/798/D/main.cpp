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

const int MAX = 1000*1000 + 10;
int n;
vi G[MAX];
int mx[MAX],mx2[MAX],dp[MAX],P[MAX];

int main(){
	scanf("%d",&n); n++;
	dp[0] = -1;
	range(i,2,n) {
		int p; scanf("%d",&p);
		P[i] = p;
		int u = i;
		int debug = u == 11;
		while(p >= 1){
			if(u != mx[p] && dp[u] > dp[mx2[p]]) mx2[p] = u;
			if(dp[mx2[p]] > dp[mx[p]]) swap(mx[p],mx2[p]);
			int nv = max(dp[mx[p]],dp[mx2[p]] + 1);
			if(debug) cerr << nv << " " << dp[p] << " " << u << " " << mx[p] << " " << mx2[p] << endl;
			if(nv == dp[p]) break;
			dp[p] = nv;
			u = P[p];
			swap(u,p);
		}
		//cerr << dp[1] << " " << mx[1] << " " << mx2[1] << endl;
		printf("%d%c",dp[1]," \n"[i == n]);
		//break;
	}
	return 0;
}
