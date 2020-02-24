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


int n, m, k;
int special[1 << 20];
vi G[1 << 20];
int dist[1 << 20];
bool is_special[1 << 20];

queue<int> q;
void bfs(){
	fill(dist, dist + n + 1, INT_MAX);
	dist[1] = 0;
	q.push(1);
	while(!q.empty()){
		int u = q.front(); q.pop();
		for(int v : G[u]) if(dist[u] + 1 < dist[v]){
			dist[v] = dist[u] + 1;
			q.push(v);
		}
	}
}

int cnt[1 << 20];



int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	scanf("%d %d %d", &n, &m, &k);
	loop(i, k) {
		scanf("%d", special + i);
		is_special[special[i]] = 1;
	}
	loop(e, m){
		int a, b; scanf("%d %d", &a, &b);
		G[a].pb(b);
		G[b].pb(a);
	}
	bfs();
	
	loop(i, k) cnt[dist[special[i]]]++;
	sort(special, special + k, [](const int & a, const int & b){
		return dist[a] < dist[b];
	});
	
	pair<pair<int, ll>, pi> cand(pair<int, ll>(INT_MAX, 0), pi(0, 0));
	loop(i, k-1) {
		int a = special[i];
		int b = special[i+1];
		int d = dist[b] - dist[a];
		ll c = - cnt[dist[a]] * (ll)cnt[dist[b]];
		cand = min(cand, pair<pair<int, ll>, pi>(pair<int, ll>(d, c), pi(a, b)));
	}

	int a = cand.second.first;
	int b = cand.second.second;
	G[a].pb(b);
	G[b].pb(a);
	
	bfs();
	printf("%d\n", dist[n]);

	
	return 0;
}
