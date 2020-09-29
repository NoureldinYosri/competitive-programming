#pragma GCC optimize ("O3")
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

const vector<string> modes = {"AIR", "SEA", "RAIL", "TRUCK"};
char buffer[1 << 20];
vi changeCost;
vi dist[4];
vector<vector<pair<int, pi>>> adj;
int n;
priority_queue<pair<int, pi>, vector<pair<int, pi>>, greater<pair<int, pi>>> pq;

void tc(){
	scanf("%d", &n);
	changeCost.clear();
	changeCost.resize(n);
	adj.clear();
	adj.resize(n);
	map<string, int> name2id;
	loop(i, n){
		scanf("%s %d", buffer, &changeCost[i]);
		name2id[string(buffer)] = i;
	}
	int m; scanf("%d", &m);
	loop(e, m){
		scanf("%s", buffer);
		int a = name2id[string(buffer)];
		scanf("%s", buffer);
		int b = name2id[string(buffer)];
		scanf("%s", buffer);
		int t = find(all(modes), string(buffer)) - modes.begin();
		int c; scanf("%d", &c);
		adj[a].emplace_back(c, pi(t, b));
		adj[b].emplace_back(c, pi(t, a));
	}
	
	loop(t, 4) {
		dist[t].clear();
		dist[t].resize(n, 1 << 29);
	}
	scanf("%s", buffer); int src = name2id[string(buffer)];
	scanf("%s", buffer); int to = name2id[string(buffer)];
	
	
	loop(t, 4){
		dist[t][src] = 0;
		pq.emplace(0, pi(t, src));
	}
	
	while(!pq.empty()){
		auto [d, tu] = pq.top(); pq.pop();
		auto [t, u] = tu;
		if(d != dist[t][u]) continue;
		for(auto [cost, tv] : adj[u]){
			auto [tn, v] = tv;
			int nd = d + cost + (tn != t) * changeCost[u];
			if(nd < dist[tn][v]){
				dist[tn][v] = nd;
				pq.emplace(nd, pi(tn, v));
			}
			
		}
	}
	
	int ans = INT_MAX;
	loop(t, 4) ans = min(ans, dist[t][to]);
	printf("%d\n", ans);
}


int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	int T; scanf("%d", &T);
	while(T--) tc();
	return 0;
}
