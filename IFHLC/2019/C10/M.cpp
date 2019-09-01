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
#define tc() int T; scanf("%d",&T); for(int t = 1;t <= T;t++)
using namespace std;

using edge = pair<ll,int>;
const ll oo = 1LL << 60;
const int MAXN = 100*1000 + 10;
int n,L,R,C;
int A[MAXN];
ll dist[MAXN];

int m;
set<pair<ll,int> > S[MAXN];
void renumber(){
	vi B{A+1,A+n+1};
	sort(all(B));
	B.resize(unique(all(B)) - B.begin());
	m = sz(B);
	for(int i = 1;i <= n;i++) {
		A[i] = lower_bound(all(B),A[i]) - B.begin();
		S[A[i]].insert(mp(oo,i));
	}
}

using auxDS = priority_queue<edge,vector<edge>,greater<edge> >;

inline void update(int s,ll d,auxDS & pq) {
	if(d >= dist[s]) return;
	int id = A[s];
	S[id].erase(mp(dist[s],s));
	S[id].insert(mp(d,s));
	dist[s] = d;
	pq.push(mp(d,s));
	d += C;
	while(S[id].rbegin()->first > d) {
		auto p = *S[id].rbegin();
		S[id].erase(p);
		int u = p.second;
		dist[u] = d;
		S[id].insert(mp(d,u));
		pq.push(mp(d,u));
	}
}

ll dijkstra(int s,int e) {
	auxDS pq;
	for(int i = 1;i <= n;i++) dist[i] = oo;
	update(s,0,pq);
	while(!pq.empty()){
		edge e = pq.top(); pq.pop();
		ll d = e.first;
		int u = e.second;
		if(dist[u] < d) continue;
		if(u-1 >= 1) update(u-1,d + L,pq);
		if(u+1 <= n) update(u+1,d + R,pq);
	}
	return dist[e];
}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	scanf("%d %d %d %d",&n,&L,&R,&C);
	int st,en;
	scanf("%d %d",&st,&en);
	for(int i = 1;i <= n;i++) scanf("%d",A + i);
	renumber();
	cout << dijkstra(st,en) << endl;
	return 0;
}
#endif
