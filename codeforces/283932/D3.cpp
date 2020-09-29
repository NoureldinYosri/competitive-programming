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


int n, m, L; 
vp E[1 << 20];
queue<int> q;
int dist[1 << 20];
int parent[1 << 20];

bool can(int W){
	memset(dist, -1, sizeof dist);
	q.push(1);
	dist[1] = 0;
	while(!q.empty()){
		int u = q.front(); q.pop();
		for(auto [v, w] : E[u]) if(w <= W && dist[v] == -1){
			dist[v] = dist[u] + 1;
			q.push(v);
			parent[v] = u;
		}
	}
	return dist[n] != -1 && dist[n] <= L;
}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	scanf("%d %d %d", &n, &m, &L);
	int s = 0, e = 0;
	loop(t, m){
		int a, b, c; scanf("%d %d %d", &a, &b, &c);
		E[a].emplace_back(b, c);
		e = max(e, c);
	}
	while(s < e){
		int m = (s + e) >> 1;
		if(can(m)) e = m;
		else s = m+1;
	}

	if(!can(s)) cout << -1 << endl;
	else {
		printf("%d\n", dist[n]);
		vi path;
		for(int u = n; u != 1; u = parent[u]) path.pb(u);
		path.pb(1);
		reverse(all(path));
		loop(i, sz(path)) printf("%d%c", path[i], " \n"[i == dist[n]]);
	}
	return 0;
}
