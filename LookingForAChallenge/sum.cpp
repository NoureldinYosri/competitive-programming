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

const int oo = 1e9 + 3;
const int MAXN = 5 << 10, MAXA = 50*1000 + 10;
int A[MAXN], n;
int ring;
ll dist[MAXA];


using state = pi;

void dijkstra(){
	ring = *min_element(A, A + n);
	fill(dist, dist + ring, oo);
	dist[0] = 0;
	priority_queue<state, vector<state>, greater<state>> pq;
	pq.emplace(0, 0);
	while(!pq.empty()){
		auto [d, u] = pq.top(); pq.pop();
		if(dist[u] != d) continue;
		loop(i, n){
			int v = (u + A[i])%ring;
			int wd = d + A[i];
			if(wd < dist[v]){
				dist[v] = wd;
				pq.emplace(wd, v);
			} 
		}
	}
}

void fix(){
	vi aux;
	set<int> S;
	sort(A, A + n);
	ring = A[0];
	loop(i, n) {
		int r = A[i]%ring;
		if(S.count(r)) continue;
		S.insert(r);
		aux.pb(A[i]);
	}
	copy(all(aux), A);
	n = sz(aux);
}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	scanf("%d", &n);
	loop(i, n) scanf("%d", A + i);
	fix();
	dijkstra();
	int m; scanf("%d", &m);
	loop(i, m){
		int x; scanf("%d", &x);
		puts((dist[x%ring] <= x) ? "TAK" : "NIE");
	}
	return 0;
}
