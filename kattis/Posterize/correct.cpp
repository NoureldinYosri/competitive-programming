/*#pragma GCC optimize ("O3")
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

const ll oo = 1LL << 60;
ll cost[300][300],dp[300][300];
int cnt[300];

int main(){
	#ifndef ONLINE_JUDGE
		freopen("in.in", "r", stdin);
	#endif
	int d,K; cin >> d >> K;
	loop(i,d) {
		int r,p; cin >> r >> p;
		r ++;
		cnt[r] += p;
	}

	fill(&cost[0][0],&cost[300][0],oo);
	fill(&dp[0][0],&dp[300][0],oo);
	dp[0][0] = 0;
	for(int k = 1;k <= 256;k++){
		for(int i = 1;i <= 256;i++){
			ll sum = 0;
			for(int j = i;j <= 256;j++){
				sum += abs(j - k)*1LL*abs(j - k)*1LL*cnt[j];
				cost[i][j] = min(cost[i][j],sum);
			}
		}
	}
 	for(int e = 1;e <= 256;e++){
		for(int k = 1;k <= K;k++){
			dp[e][k] = oo;
			for(int s = 1;s <= e;s++)
				dp[e][k] = min(dp[e][k],dp[s - 1][k - 1] + cost[s][e]);
		}
	}
	cout << dp[256][K] << endl;
	return 0;
}
*/
