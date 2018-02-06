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

const ll oo = 1LL << 60;
const int MAX = 100001;
ll W[MAX],sW[MAX],WS[MAX];
int n,K;
ll dp[15][MAX];


double g(pl A,pl B) {
	assert(A.xx != B.xx);
	// A.xx * x + A.yy > B.xx *x + B.yy
	// x > (B.yy - A.yy)/(A.xx - B.xx)
	return (B.yy - A.yy + 0.0)/(A.xx - B.xx);
}

ll eval(pl A,int x) {
	return A.xx*x + A.yy;
}

int main(){
#ifdef HOME
	freopen("in.in","r",stdin);
#endif
	scanf("%d %d",&n,&K);
	range(i,1,n){
		scanf("%lld",W + i);
		sW[i] = sW[i - 1] + W[i];
		WS[i] = WS[i - 1] + i*W[i];
	}
	range(i,1,n) dp[0][i] = oo;
	dp[0][0] = 0;


	deque<pl> dq;
	for(int k = 1;k <= K;k++) {
		dq.clear();
		for(int j = 1;j <= n;j++) {
			// add new line;
			pl newLine (-j,dp[k-1][j-1] + j*sW[j-1] - WS[j-1]);
			while(sz(dq) > 1 && g(dq[sz(dq)-2],dq[sz(dq)-1]) >= g(dq[sz(dq)-1],newLine))
				dq.pop_back();
			dq.push_back(newLine);

			// compute answer
			// min dp[k-1][i-1] + sum (k-i) W[k] for i <= k <= j
			// min dp[k-1][i-1] + sum k*W[k] - i*sum W[k]
			// min dp[k-1][i-1] + WS[j] - WS[i-1] - i*(sW[j] - sW[i-1])
			// min dp[k-1][i-1] + WS[j] - WS[i-1] - i*sW[j] + i*sW[i-1]
			// min dp[k-1][i-1] - WS[i-1] + i*sW[i-1] - i*sW[j] + WS[j]
			// a = -i,b = dp[k-1][i-1] - WS[i-1] + i*sW[i-1]
			int s = 0,e = sz(dq) - 1;
			while(e - s > 1) {
				int m1 = s + (e-s+1)/3,m2 = m1 + (e-s+1)/3;
				if(eval(dq[m1],sW[j]) < eval(dq[m2],sW[j])) e = m2 - 1;
				else s = m1 + 1;
			}
			dp[k][j] = WS[j] + min(eval(dq[s],sW[j]),eval(dq[e],sW[j]));
//			for(auto p : dq) cerr << WS[j] + eval(p,sW[j]) << " ";
//			cerr << endl;
		}
//		prArr(dp[k],n+1,ll);
	}
	printf("%lld\n",dp[K][n]);

	return 0;
}
