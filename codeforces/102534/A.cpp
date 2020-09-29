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
 
const int MAX = 2 << 10;
const int oo = 1 << 29;
string s;
int n;
vi L, R;
vi vis;
vector<vi> G;

int cost = 0;
bool dfs(int u){
	if(vis[u]) return 0;
	vis[u] = 1;
	for(int v : G[u]) if(R[v] == -1 || dfs(R[v])){
		L[u] = v;
		if(R[v] != -1) cost += s[R[v]] - 'A' + 1;
		R[v] = u;
		cost -= s[u] - 'A' + 1;
		return 1;
	}
	return 0;
}

 
int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	int k;
	cin >> k >> s;
	n = sz(s);
	L.resize(n, -1);
	R.resize(n, -1);
	vis.resize(n);
	G.resize(n);
	loop(j, n) loop(i, j) if(s[i] < s[j]) G[i].pb(j);
	loop(i, n){
		sort(all(G[i]), [](const int & a, const int & b){
			return tie(s[a], a) > tie(s[b], b);
		});
	}
	int f = n;
	loop(i, n) cost += s[i] - 'A';
	int m = INT_MAX;
	if(cost <= k) m = n;
	
	loop(i, n) {
		fill(all(vis), 0);
		if(dfs(i)){
			f--;
			if(cost <= k) 
				m = f;
			cerr << f << " " << cost << endl;
		}
	}
	print(R, int);
	if(m != INT_MAX) cout << m << endl;
	else puts("Impossible");
	
	return 0;
}
