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

const int MAX = 100*1000 + 10;
vi head, choice, vis;
vi fr, to, cost, orig, nxt, id, W, aux;
vi usedAt;
vector<list<int>> covers;
int n, m;



void init(){
	head.clear(), choice.clear();
	fr.clear(), to.clear();
	cost.clear(), nxt.clear();
	id.clear();
	W.clear();
	vis.clear();
	aux.clear();

	aux.resize(n);
	vis.resize(n);
	head.resize(n, -1);
	choice.resize(n, -1);
	id.resize(n);
	loop(i, n) id[i] = i;
	W.resize(n, 1);
}

void add_edge(int a, int b, int c){
	int e = sz(fr);
	fr.pb(a);
	to.pb(b);
	cost.pb(c);
	orig.pb(c);
	usedAt.pb(0);
	covers.emplace_back();
	nxt.pb(head[a]);
	head[a] = e;
}

int find(int a){
	return id[a] = (a == id[a]) ? a : find(id[a]);
}
void join(int a, int b){
	a = find(a), b = find(b);
	if(a == b) return;
	if(W[a] < W[b]) swap(a, b);
	id[b] = a;
	W[a] += W[b];
}


int MST(int depth){
	int ret = 0;
	int root = find(0);
	fill(all(vis), 0);
	fill(all(choice), -1);
	fill(all(aux), 0);
	loop(e, m) {
		int a = find(fr[e]), b = find(to[e]);
		if(a == b || b == root) continue;
		if(choice[b] == -1 || cost[e] < cost[choice[b]])
			choice[b] = e;
	}
	
	loop(i, n) if(i != root && i == find(i) && choice[i] != -1) {
		ret += cost[choice[i]];
		usedAt[choice[i]] = depth;
//		int e = choice[i];
//		cerr << fr[e] << " " << to[e] << " " << cost[e] << endl;
	}
//	cerr << endl;
		
	int vis_num = 0;
	static vector<vi> cycles;
	static vi V;
	cycles.clear();
	loop(i, n) if(i != root && i == find(i) && !vis[i]){
		int j = i;
		vis_num++;
		V.clear();
		while(!vis[j] && j != root){
			V.pb(j);
			vis[j] = vis_num;
			int e = choice[j];
			if(e == -1){
				puts("-1");
				exit(0);
			}
			assert(e != -1);
			j = find(fr[e]);
		}
		if(vis_num == vis[j]) {
			cycles.emplace_back();
			while(V.back() != j){
				cycles.back().pb(V.back());
				V.pop_back();
			}
			cycles.back().pb(j);
//			cycles.emplace_back(V);
//			print(cycles.back(), int);
		}
	}
	
	if(!cycles.empty()){
		ret = 0;
		for(auto & V: cycles){
			for(int v : V){
				aux[v] = cost[choice[v]];
				ret += cost[choice[v]];
			}
		}
		loop(e, m) {
			int a = find(fr[e]), b = find(to[e]);
			if(a == b || choice[b] == -1) continue;
			if(choice[b] == e) continue;
			cost[e] -= aux[b];
			covers[e].pb(choice[b]);
		}
		for(auto & V : cycles) {
			for(int v : V) 
				join(v, V.back());
			for(int v : V) {
				int e = choice[v];
				assert(find(fr[e]) == find(to[e]));
			}
		}		
		ret += MST(depth + 1);		
	}
	return ret;
}

void dfs(int e){
	if(!usedAt[e]) return ;
	usedAt[e] = 0;
	for(int et : covers[e]) usedAt[et] = 0;
}

int main(){
	freopen("input.txt", "r", stdin);
#ifndef HOME
	freopen("output.txt", "w", stdout);
#endif
	scanf("%d %d", &n, &m);
	init();
	loop(e, m){
		int a, b, c;
		scanf("%d %d %d", &a, &b, &c);
		a--, b--;
		add_edge(a, b, c);
	}

//	cerr << MST(1) << endl;
	MST(1);
	vi ord(m);
	loop(i, m) ord[i] = i;
	sort(all(ord), [](const int & a, const int & b){
		return usedAt[a] > usedAt[b];
	});
	
	vi ans;
	for(int e : ord) if(usedAt[e]){
//		cerr << fr[e] + 1 << " " << to[e] + 1 << " " << cost[e] << endl;
		if(orig[e]) ans.pb(e + 1);
		dfs(e);
	}

	

	printf("%d\n", sz(ans));
	for(int e : ans) printf("%d ", e);
	puts("");
	return 0;
}
