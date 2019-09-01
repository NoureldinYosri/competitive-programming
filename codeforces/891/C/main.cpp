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
#define tc() int T; scanf("%d",&T); for(int t = 1;t <= T;t++)
using namespace std;

const int MAX = 500*1000 + 10,MAXLG = 20;
int fr[MAX],to[MAX],cost[MAX],n,m;
vi E[MAX];
int P[MAX][MAXLG],onEdge[MAX][MAXLG];
int dfs_in[MAX],dfs_out[MAX],dfs_time,depth[MAX];

void read(){
	scanf("%d %d",&n,&m);
	loop(e,m) scanf("%d %d %d",fr + e,to + e,cost + e);
}

int id[MAX],W[MAX];

vector<pair<int*,int> > ST;

int find(int a) {
	if(a == id[a]) return a;
	ST.emplace_back(&id[a],id[a]);
	return id[a] = find(id[a]);
}
bool join(int a,int b) {
	a = find(a),b = find(b);
	if(a == b) return 0;
	if(W[a] < W[b]) swap(a,b);
	ST.emplace_back(&W[a],W[a]);
	ST.emplace_back(&id[b],id[b]);
	W[a] += W[b];
	id[b] = a;
	return 1;
}

map<int,map<int,vi>> R;
bool ans[MAX];

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	read();
	int Q; scanf("%d",&Q);
	loop(q,Q){
		int k; scanf("%d",&k);
		while(k--) {
			int e; scanf("%d",&e); e--;
			R[cost[e]][q].push_back(e);
		}
		ans[q] = 1;
	}
	vi edges;
	loop(e,m) edges.push_back(e);
	sort(all(edges),[](const int & a,const int & b) {
		return cost[a] < cost[b];
	});
	for(int i = 1;i <= n;i++) id[i] = i,W[i] = 1;
	for(int i = 0;i < m;) {
		int w = cost[edges[i]];
		for(auto ob : R[w]) {
			int q = ob.first;
			if(!ans[q]) continue;
			int s = sz(ST);
			for(int e : R[w][q])
				ans[q] &= join(fr[e],to[e]);
			while(sz(ST) > s) {
				auto mem = ST.back(); ST.pop_back();
				*mem.first = mem.second;
			}
		}
		while(i < m && cost[edges[i]] == w) {
			int e = edges[i++];
			join(fr[e],to[e]);
		}
	}
	loop(q,Q) puts(ans[q] ? "YES" : "NO");
	return 0;
}
