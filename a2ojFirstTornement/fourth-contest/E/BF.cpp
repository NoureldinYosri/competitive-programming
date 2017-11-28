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

const int MAX = 300*1000 + 10;
int n,m,k;
int A[MAX],B[MAX],C[MAX],IDX[MAX];
vector<vi> P;
vector<vl> dp;
vi G[MAX];

ll solve(int cur,int d) {
	if(d == m) return 0;
	ll & ret = dp[d][cur-1];
	if(ret != -1) return ret;
	ret = solve(cur,d+1);
	for(int x : G[cur])
		ret = max(ret,solve(x,d+1));
	ret += P[d][cur-1];
	return ret;
}

int main(){
	#ifdef HOME
		freopen("in.in", "r", stdin);
	#endif
	scanf("%d %d %d",&n,&m,&k);
	P = vector<vi> (m,vi(n));
	loop(i,m) {
		loop(j,n) scanf("%d",&P[i][j]);
//		print(P[i],int);
	}
	memset(IDX,-1,sizeof IDX);
	loop(i,k) {
		scanf("%d %d %d",A + i,B + i,C + i);
		range(j,A[i],B[i]) G[j].pb(C[i]),G[C[i]].pb(j);
	}
	dp = vector<vl> (m,vl(n,-1));
	ll ans = 0;
	range(i,1,n) ans = max(ans,solve(i,0));
	cout << ans << endl;

	return 0;
}
