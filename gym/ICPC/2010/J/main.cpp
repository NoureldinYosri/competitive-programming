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

int n;
int demand[15];
int dp[1 << 15][101];
int lg[1 << 15];

int solve(int msk,int w){
	if(popcnt(msk) == 1) return 1;
	if(dp[msk][w] != -1) return dp[msk][w];

	vi V;
	int in = 0,H = 0;
	loop(i,n) if(msk & (1 << i)) V.pb(i),in += demand[i];
	H = in/w;

	int & ret = dp[msk][w]; ret = 0;
	for(int cur = 1;cur + 1 < (1 << sz(V)) && !ret;cur++ ){
		int tot = 0,rmsk = 0;
		loop(i,sz(V)) if(cur & (1 << i)) {
			rmsk |= 1 << V[i];
			tot += demand[V[i]];
		}
		if(tot%w == 0 && tot/w + (in - tot)/w == H) ret = solve(rmsk,w) && solve(msk ^ rmsk,w);
		if(tot%H == 0 && tot/H + (in - tot)/H == w) ret |= solve(rmsk,H) && solve(msk ^ rmsk,H);
	}
	return ret;
}

int main(){
	freopen("logger.out","w",stderr);
	#ifndef ONLINE_JUDGE
		freopen("input.in", "r", stdin);
		freopen("output.out", "w", stdout);
	#endif
	loop(i,15) lg[1 << i] = i;
	for(int t = 1;scanf("%d",&n) == 1 && n;t++){
		int H,W,tot = 0;
		scanf("%d %d",&H,&W);
		loop(i,n) {
			scanf("%d",demand + i);
			tot += demand[i];
		}
		bool can = 0;
		if(tot%W != 0 || tot / W != H) can = 0;
		else {
			memset(dp,-1,sizeof dp);
			can = solve((1 << n) - 1,W);
		}
		printf("Case %d: %s\n",t,can ? "YES" : "NO");
	}
	return 0;
}
