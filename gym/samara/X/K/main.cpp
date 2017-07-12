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

const int MAX = 200000 + 1000;
pi E[MAX];
int X[MAX],Y[MAX],n;
int val[MAX];
pair<ll,ll> dp[MAX];
int vis[MAX];
int goTo[MAX],use[MAX];

pair<ll,ll> solve(int cur){
	if(cur == n) return mp(0,0);
	if(vis[cur]) return dp[cur];
	vis[cur] = 1;
	pair<ll,ll> & ret = dp[cur];
	goTo[cur] = cur + 1;
	use[cur] = 0;
	ret = solve(cur + 1);
	int who = E[cur].yy;
	int nxt = lower_bound(X + cur + 1,X + n,Y[who]) - X;
	auto tmp = solve(nxt);
	tmp.xx += val[who];
	tmp.yy += Y[who] - X[cur];
	if(tmp.xx > ret.xx) {
		ret = tmp;
		goTo[cur] = nxt;
		use[cur] = 1;
	}
	else if(tmp.xx == ret.xx && tmp.yy < ret.yy) {
		ret.yy = tmp.yy;
		goTo[cur] = nxt;
		use[cur] = 1;
	}
	return ret;
}

int main(){
	freopen("logger.out","w",stderr);
	#ifndef ONLINE_JUDGE
		freopen("input.in", "r", stdin);
		freopen("output.out", "w", stdout);
	#endif
	scanf("%d",&n);
	loop(i,n) scanf("%d %d %d",&E[i].xx,Y + i,val + i),E[i].yy = i;
	sort(E,E + n);
	loop(i,n) X[i] = E[i].xx;
	auto ans = solve(0);
	vi V;
	for(int cur = 0;cur < n;cur = goTo[cur]){
		if(use[cur]) V.pb(E[cur].yy + 1);
	}
	printf("%d %lld %lld\n",sz(V),ans.xx,ans.yy);
	for(int x : V) printf("%d ",x);
	return 0;
}
