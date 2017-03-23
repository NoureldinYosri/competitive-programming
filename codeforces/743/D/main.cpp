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

const ll NINF = -(1LL << 61);
const int MAX = 1 << 20;
int A[MAX],n;
vi G[MAX];
ll ans = NINF;
int cond = 0;


ll dfs(int u,int p,ll & mx){
	ll sum = A[u];	
	int ctr = 0;
	for(int v : G[u]) if(v != p){
		ll mx2 = NINF; 
		sum += dfs(v,u,mx2);
		if(ctr) ans = max(ans,mx + mx2),cond = 1;
		mx = max(mx,mx2);
		ctr++;
	}
	mx = max(mx,sum);
	return sum;
}

int main(){
	scanf("%d",&n);
	loop(i,n) scanf("%d",A + i + 1);
	loop(i,n-1){
		int a,b; scanf("%d %d",&a,&b);
		G[a].pb(b);
		G[b].pb(a);
	}	
	ll a = NINF;
	dfs(1,0,a);	
	if(cond && ans > NINF) cout << ans << endl;
	else cout << "Impossible" << endl;
	return 0;
}
