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

const int MAX = 1e5 + 1e2;
vi G[MAX];
int siz[MAX],n,m;
int fr[MAX],to[MAX],len[MAX];
double ans = 0;

ll C(ll n,int k){
	if(k == 1) return n;
	return n * (n - 1) / 2;
}

int dfs(int u,int p){
	siz[u] = 1;
	for(int e : G[u]) {
		if(fr[e] == p) continue;
		if(to[e] == u) swap(to[e],fr[e]);
		int v = to[e];
		if(v != p){
			siz[u] += dfs(v,u);
			ll tmp = C(siz[v],1) * C(n - siz[v],2) * len[e];
			tmp += C(siz[v],2) * C(n - siz[v],1) * len[e];
			//cerr << e << " " << tmp << endl;
			ans += tmp;
		}	
	}
	return siz[u];
}

int main(){
	scanf("%d",&n);
	range(i,1,n-1){
		scanf("%d %d %d",fr + i,to + i,len + i);
		G[fr[i]].pb(i);
		G[to[i]].pb(i);
	}
	dfs(1,0);
	ll tot = n * (n - 1LL) * (n - 2LL) / 6;
	scanf("%d",&m);
	while(m--){
		int e,c; scanf("%d %d",&e,&c);
		ll tmp = C(siz[to[e]],1) * C(n - siz[to[e]],2);
		tmp += C(siz[to[e]],2) * C(n - siz[to[e]],1);
		ans -= tmp * (len[e] - c);
		len[e] = c;
		printf("%.10f\n",ans * 2.0 / tot);
	//	cerr << e << " " << tmp << " " << fr[e] << " " << to[e] << endl;
	}
	
	
	return 0;
}
