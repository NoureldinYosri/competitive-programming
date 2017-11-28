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

ll oo = 1LL << 60;
ll dp[100][1 << 10];
int A[100],n;
int B[10],m;

ll solve(int cur,int msk) {
	if(!msk) return 0;
	if(cur == n) return oo;
	ll & ret = dp[cur][msk];
	if(ret != -1) return ret;
	ret = oo;
	vi V;
	loop(i,m) if(msk & (1 << i)) V.pb(i);
	loop(tmsk,1 << sz(V)) {
		int submsk = 0;
		ll val = 0;
		loop(i,sz(V))
			if(tmsk & (1 << i)){
				submsk |= 1 << V[i];
				val += B[V[i]];
			}
		ret = min(ret,solve(cur+1,msk ^ submsk) + max(val - A[cur],0LL));
	}
//	cerr << cur << " " << msk << " " << ret << endl;
	return ret;
}

int main(){
	#ifdef HOME
		freopen("in.in", "r", stdin);
	#endif
	scanf("%d %d",&n,&m);
	loop(i,n) scanf("%d",A + i);
	loop(i,m) scanf("%d",B + i);
	sort(A,A + n);
	reverse(A,A + n);
	n = min(n,m);
	memset(dp,-1,sizeof dp);
	cout << solve(0,(1 << m) - 1) << endl;
	return 0;
}
