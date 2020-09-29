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

struct DSU{
	vi W, id;
	vector<pair<int*, int>> hist;
	DSU(){}
	void clear(){
		hist.clear();
		iota(all(id), 0);
		fill(all(W), 1);
	}
	DSU(int n){
		W.resize(n);
		id.resize(n);
		clear();
	}
	void replace(int *ptr, int v){
		hist.emplace_back(ptr, *ptr);
		*ptr = v;
	}
	void revert(int checkpoint){
		while(sz(hist) > checkpoint){
			auto [ptr, v] = hist.back(); hist.pop_back();
			*ptr = v;
		}
	}
	int find(int a){
		if(a == id[a]) return a;
		int p = find(id[a]);
		replace(&id[a], p);
		return p;
	}
	void join(int a, int b){
		a = find(a), b = find(b);
		if(a == b) return;
		if(W[a] < W[b]) swap(a, b);
		replace(&id[b], a);
		replace(&W[a], W[a] + W[b]);
	}
	bool areConnected(int a, int b){
		return find(a) == find(b);
	}
};

const int MAXE = 40000;
int visNum;
int visID[MAXE], fr[MAXE], to[MAXE], cost[MAXE], flags[MAXE];
int n, m;
DSU dsu;

ll kruskal(vi & E, int msk, bool doClear){
	sort(all(E), [](const int & a, const int & b){
		return cost[a] < cost[b];
	});		
//	cerr << "in: ";
//	for(int e : E) cerr << pi(cost[e], e);
//	cerr << endl;
	if(doClear) dsu.clear();
	ll ret = 0;
	for(int e : E){
		int a = fr[e], b = to[e];
		if(!dsu.areConnected(a, b)){
			dsu.join(a, b);
			ret += cost[e];
			flags[e] |= msk;
//			cerr << mp(cost[e], pi(a, b)) << " ";
		}
	}
//	cerr << endl;
	return ret;
}

void work(vp & updates){
	if(updates.empty()) return;
	visNum++;
	for(auto [e, _] : updates){
		visID[e] = visNum;
	}
	static vi edgesClasses[2], everyEdge(m);
	iota(all(everyEdge), 0);
	loop(c, 2) edgesClasses[c].clear();
	loop(e, m) edgesClasses[visID[e] != visNum].pb(e);
	
	static vi oldCost, newCost;
	if(oldCost.empty()){
		oldCost.resize(m);
		newCost.resize(m);
	}
	for(int e : edgesClasses[0]){
		oldCost[e] = newCost[e] = cost[e];
	}
	for(auto [e, c] : updates){
		newCost[e] = min(newCost[e], c);
	}
	
	fill(flags, flags + m, 0);
	//prArr(flags, m, int);
//	kruskal(everyEdge, 1, true);
	for(int e : edgesClasses[0]) cost[e] = newCost[e];
	kruskal(everyEdge, 2, true);
	for(int e : edgesClasses[0]) cost[e] = oldCost[e];
	kruskal(edgesClasses[1], 4, true);
	edgesClasses[1].clear();
	//prArr(flags, m, int);
	for(int e : everyEdge) {
		if(flags[e] == 6){
			assert(visID[e] != visNum);
			edgesClasses[1].pb(e);
		} else if(flags[e] && visID[e] != visNum){
			edgesClasses[0].pb(e);
		}
	}	 
	//print(edgesClasses[1], int);
	ll tot = kruskal(edgesClasses[1], 0, true);
	int checkpoint = dsu.hist.size();
	for(auto [e, c] : updates){
		cost[e] = c;
		ll tmp = tot + kruskal(edgesClasses[0], 0, false);
		printf("%lld\n", tmp);
		dsu.revert(checkpoint);
	}
}

int main(){
	freopen("input.txt", "r", stdin);
#ifndef HOME
	freopen("output.txt", "w", stdout);
#endif
	scanf("%d %d", &n, &m);
	dsu = DSU(n);
	loop(e, m){
		scanf("%d %d %d", fr + e, to + e, cost + e);
		fr[e]--, to[e]--;
	}
	int Q; scanf("%d", &Q);
	vp updates;
	int B = sqrt(n + m + Q);
	loop(i, Q){
		int e, c; scanf("%d %d", &e, &c);
		updates.emplace_back(e - 1, c);
		if(sz(updates) == B) {
			work(updates);
			updates.clear();
		}
	}
	work(updates);
	return 0;
}
