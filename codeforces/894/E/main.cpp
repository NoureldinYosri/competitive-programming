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

const int MAX = 1000*1000 + 10;
map<int,vi> G[MAX];
int n,m;
ll self[MAX];
ll score[MAX];

ll f(int w) {
	if(w == 0) return 0;
	// w ,w - 1,w - (1 + 2) , w - (1 + 2 + 3)
	int s = 1,e = 20*1000;
	while(s < e){
		int m = s + (e - s + 1)/2;
		if(m*(m + 1LL)/2 <= w) s = m;
		else e = m - 1;
	}
	//3 2 0
	//8 7 6 3
	ll tmp = (s*(s + 1LL)*(2*s + 1LL))/6 + s*(s + 1LL)/2;
	assert(tmp%2 == 0);
	tmp /= 2;
	ll ret = w*(s+1LL) - tmp;
//	cerr << w << " " << s << " -> " << w*(s + 1) << "-" << tmp << "=" << ret << endl;
	assert(ret >= w);
	return ret;
}


const int MAXV = MAX;
vi ST;
int dfs_in[MAXV],dfs_low[MAXV],dfs_time;
bool inStack[MAXV];
int SCC_id[MAXV],SCC_cnt;
vi SCC[MAXV];
vector<pair<int,ll> > SCC_adj[MAXV];

void tarjanSCC(int u) {
	dfs_in[u] = dfs_low[u] = dfs_time++;
	ST.pb(u);
	inStack[u] = true;
	for(auto e : G[u]){
		int v = e.xx;
		if (dfs_in[v] == -1) {
			tarjanSCC(v);
			dfs_low[u] = min(dfs_low[u], dfs_low[v]);
		}
		else if (inStack[v]) {
			dfs_low[u] = min(dfs_low[u], dfs_low[v]);
		}
	}
	if (dfs_low[u] == dfs_in[u]) {
		bool done = 0;
		while(!done){
			int v = ST.back();
			SCC_id[v] = SCC_cnt;
			SCC[SCC_id[v]].pb(v);
			ST.pop_back();
			done = v == u;
			inStack[v] = 0;
		}
		SCC_cnt++;
	}
}

void compress(){
	map<int,ll> aux;
	for(int i = 0;i < SCC_cnt;i++){
		for(int u : SCC[i]){
			score[i] += self[u];
			for(auto e : G[u]){
				int v = e.xx;
				if(SCC_id[v] != i){
					for(int w : e.yy)
						aux[SCC_id[v]] = max(aux[SCC_id[v]],w + 0LL);
				}
				else{
					for(int w : e.yy)
						score[i] += f(w);
				}
			}
		}
		for(auto p : aux)
			SCC_adj[i].pb(p);
		aux.clear();
	}
}

ll dp[MAX];

ll solve(int u) {
	if(dp[u] != -1) return dp[u];
	ll & ret = dp[u];
	ret = 0;
	for(auto e : SCC_adj[u])
		ret = max(ret,e.yy + solve(e.xx));
	ret += score[u];
	return ret;
}

int main(){
	#ifdef HOME
		freopen("in.in", "r", stdin);
	#endif
	scanf("%d %d",&n,&m);
	loop(i,m){
		int a,b,w; scanf("%d %d %d",&a,&b,&w);
		if(a == b) self[a] += f(w);
		else G[a][b].pb(w);
	}
	memset(dfs_in,-1,sizeof dfs_in);
	range(u,1,n) if(dfs_in[u] == -1) tarjanSCC(u);
	compress();

	int s ; scanf("%d",&s);
	memset(dp,-1,sizeof dp);
	cout << solve(SCC_id[s]) << endl;
	return 0;
}
