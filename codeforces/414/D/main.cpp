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

const int MAX = 100'010;
vi G[MAX];
int depth[MAX],n;

void dfs(int u ,int p){
	depth[u] = depth[p] + (p != 0);
	for(int v : G[u]) if(v != p) dfs(v,u);
}

int main(){
	ll k,p; scanf("%d %lld %lld",&n,&k,&p);
	loop(i,n-1){
		int a,b; scanf("%d %d",&a,&b);
		G[a].pb(b);
		G[b].pb(a);
	}
	dfs(1,0);
	sort(depth + 1,depth + n + 1);
//	prArr(depth+1,n,int);
	ll sum = 0,h = 0,r = 1;
	ll ans = 0;
	for(int i = 2;i <= n;i++){
		sum += depth[i],h++;
		while(h * depth[i] - sum > p){
			sum -= depth[++r];
			h--;
		}
		ans = max(ans,h);
	}
	ans = min(ans,k);
	cerr << ans << endl;
	cout << ans << endl;
	return 0;
}
