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
int n;
int A[5010];
ll dp[5000][4];
bool vis[5000][4];
ll suff[5010];

int choice[5000][4];

ll solve1(int ,int);
ll solve2(int,int);


ll solve2(int cur,int k){
	if(k == 0) return suff[cur];
	if(cur == n) return oo;
	if(vis[cur][k]) return dp[cur][k];
	vis[cur][k] = 1;
	ll & ret = dp[cur][k];
	ret = oo;
	ll sum = 0;
	for(int j = cur;j <= n;j++){
		ll tmp = sum - solve1(j,k-1);
		if(tmp < ret){
			ret = tmp;
			choice[cur][k] = j;
		}
		sum += A[j];
	}

	return dp[cur][k];
}

ll solve1(int cur,int k){
	if(k == 0) return suff[cur];
	if(cur == n) return -oo;
	if(vis[cur][k]) return dp[cur][k];
	vis[cur][k] = 1;
	ll & ret = dp[cur][k];
	ret = -oo;
	ll sum = 0;
	for(int j = cur;j <= n;j++){
		ll tmp = sum - solve2(j,k-1);
		if(tmp > ret){
			ret = tmp;
			choice[cur][k] = j;
		}
		sum += A[j];
	}
	return dp[cur][k];
}


int main(){
	#ifdef HOME
		freopen("in.in", "r", stdin);
	#endif
	cin >> n ;
	loop(i,n) cin >> A[i];
	for(int i = n-1;i >= 0;i--)
		suff[i] = suff[i + 1] + A[i];

	cerr << solve1(0,3) << endl;
	int cur = 0,k = 3;
	while(cur < n && k) {
		cout << choice[cur][k] << " " ;
		cur = choice[cur][k];
		k--;
	}
	while(k--) cout << n << " ";
	return 0;
}
