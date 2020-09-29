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


void tc(){
	int n; scanf("%d", &n);
	vi A(n);
	for(int & a : A) scanf("%d", &a);
	int r1, c1, r2, c2;
	scanf("%d %d %d %d", &r1, &c1, &r2, &c2);
	r1--, r2--;
	
	ll ans = LLONG_MAX;
	map<pi, ll> dist;
	priority_queue<pair<ll, pi>, vector<pair<ll, pi>>, greater<pair<ll, pi>>> pq;
	pq.emplace(0LL, pi(r1, c1));
	dist[pi(r1, c1)] = 0;
	vector<pair<ll, pi>> nxt;
		
	while(!pq.empty() && pq.top().first < ans){
		auto [d, cell] = pq.top(); pq.pop();
		if(d != dist[cell]) continue;
		auto [r, c] = cell;
		if(r == r2) ans = min(ans, d + abs(c - c2));
		nxt.clear();
		if(r+1 < n) {
			nxt.emplace_back(1, pi(r + 1, c));
			nxt.emplace_back(A[r] - c + 1, pi(r+1, 0));
		}
		if(r) {
			nxt.emplace_back(1, pi(r - 1, c));
			nxt.emplace_back(c+1, pi(r-1, A[r-1]));
		}
		for(auto [dt, nc] : nxt){
			dt += d;
			nc.second = min(nc.second, A[nc.first]);
			if(!dist.count(nc) || dt < dist[nc]){
				dist[nc] = dt;
				pq.emplace(dt, nc);
			}
		}
	}
	printf("%lld\n", ans);
}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	int T; scanf("%d", &T);
	while(T--) tc();
	return 0;
}
