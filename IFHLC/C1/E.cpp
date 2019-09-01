#ifdef ACTIVE
#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define all(A) A.begin(),A.end()
#define pb push_back
#define mp make_pair
#define sz(A) ((int)A.size())
typedef std::vector<int> vi;
typedef std::pair<int,int> pi;
typedef std::vector<pi> vp;
typedef long long ll;
#define popcnt(x) __builtin_popcount(x)
#define LSOne(x) ((x) & (-(x)))
#define print(A,t) cerr << #A << ": "; copy(all(A),ostream_iterator<t>(cerr," " )); cerr << endl
#define prArr(A,n,t)  cerr << #A << ": "; copy(A,A + n,ostream_iterator<t>(cerr," " )); cerr << endl
#define PRESTDIO() cin.tie(0),cerr.tie(0),ios_base::sync_with_stdio(0)
#define what_is(x) cerr << #x << " is " << x << endl
#define bit_lg(x) (assert(x > 0),__builtin_ffsll(x) - 1)
const double PI = acos(-1);
template<class A,class B>
std::ostream& operator << (std::ostream& st,const std::pair<A,B> p) {
	st << "(" << p.first << ", " << p.second << ")";
	return st;
}
using namespace std;

const int MAX = 200*1000 + 10;
vi E[MAX];
int fr[MAX],to[MAX],W[MAX],n;

int farthest[MAX][2],heavyEdge[MAX][2];
ll depth[MAX];
int P[MAX];
bool onDiameter[MAX];

void dfs(int u,int p,int w) {
	depth[u] = depth[p] + w;
	P[u] = p;
	farthest[u][0] = farthest[u][1] = u;
	for(int e : E[u]) {
		int v = fr[e] + to[e] - u;
		if(v == p) continue;
		dfs(v,u,W[e]);
		int cand = farthest[v][0];
		if(depth[cand] > depth[farthest[u][1]]) {
			farthest[u][1] = cand;
			heavyEdge[u][1] = e;
		}
		int & a = farthest[u][0];
		int & b = farthest[u][1];
		if(depth[b] > depth[a]) {
			swap(a,b);
			swap(heavyEdge[u][0],heavyEdge[u][1]);
		}
	}
}

ll getDiameter(int & root){
	dfs(root,0,0);
	root = farthest[1][0];
	dfs(root,0,0);
	ll d = depth[farthest[root][0]];
	return d;
}

ll diameterDown[MAX],LengthDown[MAX];
ll diameterUp[MAX],LengthUp[MAX];

ll f(int c,set<pair<ll,int>> & S) {
	ll res = depth[farthest[c][0]] - depth[c];
	if(S.empty()) return res;
	pair<ll,int> p(-1,0);
	if(P[S.rbegin()->second] == c) {
		p = *S.rbegin();
		S.erase(p);
	}
	if(!S.empty()) res = max(res,depth[c] + S.rbegin()->first);
	if(p.second) S.insert(p);
	return res;
}

ll g(int c,set<pair<ll,int>> & S) {
	ll res = depth[c];
	if(S.empty()) return res;
	pair<ll,int> p(-1,0);
	if(S.rbegin()->second == P[c]) {
		p = *S.rbegin();
		S.erase(p);
	}
	if(!S.empty()) res = max(res,S.rbegin()->first - depth[c]);
	if(p.second) S.insert(p);
	return res;
}

void processDiameter(int root) {
	vi path;
	int snk = farthest[root][0];
	for(int u = root;u != snk;) {
		path.push_back(u);
		int e = heavyEdge[u][0];
		onDiameter[e] = 1;
		u = fr[e] + to[e] - u;
	}
	path.push_back(snk);
//	print(path,int);

	set<pair<ll,int> > S;
	diameterDown[root] = 0;
	int c = snk;
	for(int i = sz(path)-2;i >= 0;i--) {
		int u = path[i],v = path[i+1];
		diameterDown[u] = depth[snk] + depth[farthest[u][1]] - 2*depth[u];
		diameterDown[u] = max(diameterDown[u],diameterDown[v]);
		S.insert(mp(depth[farthest[u][1]] - 2*depth[u],u));
		while(c != u) {
			ll x = f(c,S),y = f(P[c],S);
			if(x < y) break;
			ll val = depth[farthest[c][1]] - 2*depth[c];
			S.erase(mp(val,c));
			c = P[c];
		}
		LengthDown[u] = f(c,S);
	}

	S.clear();
	diameterUp[root] = 0;
	c = root;
	for(int i = 1;i < sz(path);i++){
		int p = path[i-1],u = path[i];
		diameterUp[u] = depth[farthest[u][1]];
		diameterUp[u] = max(diameterUp[u],diameterUp[p]);
		S.insert(mp(depth[farthest[u][1]],u));
		while(c != u){
			int e = heavyEdge[c][0];
			int o = fr[e] + to[e] - c;
			ll x = g(o,S),y = g(c,S);
			if(y < x) break;
			S.erase(mp(depth[c],c));
			c = o;
		}
		LengthUp[u] = g(c,S);
	}

}


int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
	freopen("out.out","w",stdout);
#endif
	scanf("%d",&n);
	loop(e,n-1) {
		scanf("%d %d %d",fr + e,to + e,W + e);
		E[fr[e]].push_back(e);
		E[to[e]].push_back(e);
	}
	int root = 1;
	ll D = getDiameter(root);
	processDiameter(root);

	loop(e,n-1) {
		if(!onDiameter[e]) printf("%lld\n",D);
		else {
			int a = fr[e],b = to[e];
			if(a != P[b]) swap(a,b);
			ll ans = max(diameterDown[b],diameterUp[a]);
			ll tmp = LengthUp[a] + LengthDown[b] + W[e];
//			cerr << diameterUp[a] << " " << diameterDown[b] << endl;
//			cerr << LengthUp[a] << " " << LengthDown[b] << endl;
			ans = max(ans,tmp);
			printf("%lld\n",ans);
		}
	}
	return 0;
}
#endif
