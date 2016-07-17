#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define range(i,a,b) for(int i = (a);i <= (b);i++)
#define all(A) A.begin(),A.end()
#define PI acos(-1)
#define pb push_back
#define mp make_pair
#define sz(A) ((int)A.size())
#define vi vector<int>
#define vl vector<long>
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

const int mod = 1e9 + 7;
const int MAX = 1e5 + 1e2;
vi G[MAX],ST;
int dfsLow[MAX],dfsTime[MAX],vis[MAX],compIdx[MAX],compCnt,idx;
int val[MAX],n,m;
int mn[MAX],cnt[MAX];
ll CNT = 1,ans = 0;

void SCC(int u){
	dfsLow[u] = dfsTime[u] = idx++;
	vis[u] = 1;
	compIdx[u] = -1;	
	ST.pb(u);
	for(int v : G[u]) {
		if(!vis[v]){
			SCC(v);
			dfsLow[u] = min(dfsLow[u],dfsLow[v]);
		}
		else if(compIdx[v] == -1)
			dfsLow[u] = min(dfsLow[u],dfsLow[v]);
	}
	if(dfsLow[u] == dfsTime[u]){
		int t;
		do{
			t = ST.back(); ST.pop_back();
			compIdx[t] = compCnt;
			if(mn[compCnt] > val[t]) mn[compCnt] = val[t],cnt[compCnt] = 0;
			if(mn[compCnt] == val[t]) cnt[compCnt]++;
		}while(t != u);
		CNT = (CNT*cnt[compCnt])%mod;		
		ans += mn[compCnt];
		compCnt++;
	}
}

int main(){
	scanf("%d",&n);
	fill(mn,mn + n + 1,INT_MAX);	
	loop(i,n) scanf("%d",val + i + 1);
	scanf("%d",&m);
	while(m--){
		int a,b;		
		scanf("%d %d",&a,&b);
		G[a].pb(b);
	}
	range(i,1,n) if(!vis[i]) SCC(i);
	cerr << ans << " " << CNT << endl;
	cout << ans << " " << CNT << endl;	
	return 0;
}
