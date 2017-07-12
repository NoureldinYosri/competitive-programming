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

const int MAX = 1024;
int X[MAX],Y[MAX],R[MAX],n;
vi G[MAX];
int ord[MAX];
bool isRoot[MAX];
ll dp[MAX][2][2];
bool vis[MAX][2][2];

ll dist2(int i,int j){
	ll dx = X[i] - X[j];
	ll dy = Y[i] - Y[j];
	return dx*dx + dy*dy;
}

ll get_area(int i){
	ll r = R[i];
	return r*r;
}

ll solve(int u,bool parity,bool oparity){
	ll & ret = dp[u][parity][oparity];
	if(vis[u][parity][oparity]) return ret;
	vis[u][parity][oparity] = 1;
	ret = -(1LL << 60);
	for(int action = 0;action < n;action++){
		bool x = parity,y = oparity ;
		ll tmp = 0;
		if(action == 0) {
			y ^= 1;
			if(y) tmp += get_area(u);
			else tmp -= get_area(u);
		}
		else {
			x ^= 1;
			if(x) tmp += get_area(u);
			else tmp -= get_area(u);
		}
		for(int v : G[u])
			tmp += solve(v,x,y);
		ret = max(ret,tmp);
	}
	return ret;
}

int main(){
	#ifndef ONLINE_JUDGE
		freopen("in.in", "r", stdin);
	#endif
	scanf("%d",&n);
	loop(i,n) scanf("%d %d %d",X + i,Y + i,R + i),ord[i] = i;
	sort(ord,ord + n,[](const int & a,const int & b){
		return R[a] < R[b];
	});
	for(int i = 0;i < n;i++){
		isRoot[ord[i]] = 1;
		for(int j = i+1;j < n;j++){
			ll dr = R[ord[j]] - R[ord[i]];
			dr *= dr;
			if(dist2(ord[i],ord[j]) <= dr) {
				G[ord[j]].pb(ord[i]);
				isRoot[ord[i]] = 0;
			//	cout << ord[j] << " "  << ord[i] << endl;
				break;
			}
		}
	}
	ll ans = 0;
	memset(dp,-1,sizeof dp);
	loop(i,n) if(isRoot[i]) {
		ans += solve(i,0,0);
	}
	printf("%.10f\n",PI*ans);
	return 0;
}
