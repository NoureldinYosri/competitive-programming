#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define range(i,a,b) for(int i = (a);i <= (b);i++)
#define rrep(i,n) for(int i = (n);i >= 0;i--)
#define rran(i,a,b) for(int i = (b);i >= (a);i--)
#define step(i,a,b,d) for(int i = (a);i <= (b); i += d)
#define all(A) A.begin(),A.end()
#define PI acos(-1)
#define pb push_back
#define mp make_pair
#define sz(A) A.size()
#define len(A) A.length()
#define vi vector<int>
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
#define pre() cin.tie(0),cerr.tie(0),ios_base::sync_with_stdio(0)
using namespace std;

const int MAX = 50010;
vector<pair<int,ll> > G[MAX];
int P[MAX],IDX[MAX],n;
ll DFP[MAX],mx[MAX],mx2[MAX],ans;

void dfs(){
	fill(mx,mx + MAX,0);
	fill(mx2,mx2 + MAX,0);
	fill(P,P + MAX,0);
	fill(IDX,IDX + MAX,0);
	int u = 1; P[1] = 0; DFP[1] = 0; ans = 0;
	while(u){
		if(IDX[u] == sz(G[u])){
			ans = max(ans,mx[u] + mx2[u]);
			mx2[P[u]] = max(mx2[P[u]],mx[u] + DFP[u]);
			if(mx2[P[u]] > mx[P[u]]) swap(mx2[P[u]],mx[P[u]]);
			u = P[u];
			continue;
		}
		int v = G[u][IDX[u]].xx;
		ll d  = G[u][IDX[u]].yy;
		IDX[u]++;
		if(v == P[u]) continue;
		DFP[v] = d;
		P[v] = u;
		u = v;
	}
}

int main(){
	int T,a,b,c;
	scanf("%d",&T);
	while(T--){
		scanf("%d",&n);
		range(i,1,n) G[i].clear();
		loop(i,n - 1){
			scanf("%d %d %d",&a,&b,&c);
			G[a].pb(mp(b,c + 0LL));
			G[b].pb(mp(a,c + 0LL));
		}
		dfs();
		printf("%lld\n",ans);
	}	
	return 0;
}
