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

vi fr, to, head, capacity, nxt;
int n, m, K;

void add_edge(int a, int b, int c){
	int e = fr.size();
	fr.pb(a);
	to.pb(b);
	capacity.pb(c);
	nxt.pb(head[a]);
	head[a] = e;
}

void add_bi(int a, int b, int c1, int c2){
	add_edge(a, b, c1);
	add_edge(b, a, c2);
}

vi inEdge;

bool bfs(){
	static queue<int> q;
	while(!q.empty()) q.pop();
	fill(all(inEdge), -1); 
	q.push(0); inEdge[0] = -2;
	while(!q.empty()){
		int u = q.front(); q.pop();
		if(u == sz(inEdge)-1) return true;
		for(int e = head[u]; ~e; e = nxt[e]) if(capacity[e]) {
			int v = to[e];
			if(inEdge[v] == -1){
				inEdge[v] = e;
				q.push(v);
			}
		} 
	}
	return false;
}

vector<vi> hist;

void augment(bool retain){
	if(retain){
		hist.emplace_back();		
	}
	for(int u = sz(head)-1; u; ){
		int e = inEdge[u];
		if(retain){
			hist.back().pb(e);			
		}
		capacity[e]--;
		capacity[e^1]++;
		u = fr[e];
	}
}
int mf(bool retain){
	int ret = 0;
	while(bfs()) ret++, augment(retain);
	return ret;
}

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	scanf("%d %d %d", &n, &m, &K);
	head.resize(n+m+2, -1);
	for(int i = 1; i <= n; i++) add_bi(0, i, 1, 0);
	loop(e, K){
		int a, b; scanf("%d %d", &a, &b);
		add_bi(a, b + n, 1, 0);
	}
	for(int i = 1; i <= m; i++) add_bi(i + n, n + m + 1, 1, 0);
	
	inEdge.resize(sz(head));
	int tmp = mf(false);
	int ans = tmp;
	hist.clear();
	vi E;
	for(int e = 0; e < 2*n; e += 2) E.pb(e);
	shuffle(all(E), rng);
	for(int e : E){
		if(ans == min(n + 2, m)) break;
		capacity[e] += 2;
		int excess = mf(true);
		ans = max(ans, tmp + excess);
		if(excess == 2) {
			break;
		} 
		while(!hist.empty()){
			vi & E = hist.back();
			for(int t : E) {
				capacity[t]++;
				capacity[t^1]--;
			}
			hist.pop_back();
		}
		capacity[e] -= 2;
	}
	
	cout << ans << endl;
	return 0;
}
