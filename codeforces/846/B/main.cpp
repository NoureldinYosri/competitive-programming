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
ll dp[46][2070 + 10];
int T[46];
int n,m,k;

ll solve(int cur,int target){
	if(target <= 0) return 0;
	if(cur == n) return oo;
	if(dp[cur][target] != -1) return dp[cur][target];
	ll & ret = dp[cur][target];
	ret = oo;
	for(int i = 0;i <= k;i++)
		ret = min(ret,solve(cur + 1,target - i - (i==k)) + T[i]);
	return ret;
}



int main(){
	#ifdef HOME
		freopen("in.in", "r", stdin);
	#endif
	cin >> n >> k >> m;
	range(q,1,k)
		cin >> T[q];
	sort(T,T + k + 1);
	range(q,1,k)
		T[q] += T[q - 1];
	//prArr(T,k + 1,int);
	memset(dp,-1,sizeof dp);
	int ans = 0;
	loop(i,2070+10) if(solve(0,i) <= m) ans = i;
	cout << ans << endl;
	return 0;
}
