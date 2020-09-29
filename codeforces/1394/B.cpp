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

const int MAXN = 200*1000 + 10, MAXE = 2*MAXN;
vi E[MAXN];
int fr[MAXE], to[MAXE], cost[MAXE];
int n, m, K;
vp parent_edges[MAXN];
ll hate[55];

int p2i(pi p){
	return (p.first*(p.first + 1))/2 + p.second;
}
pi i2p(int i){
	int k = 0;
	while((k*(k + 1))/2 <= i) k++;
	k--;
	return pi(k, i - (k*(k+1))/2);
}

vi policy;

int bt(int k, ll forbidden){
	if(k == K) {
//		print(policy, int);
		return 1;
	}
	int ret = 0;
	for(int i = 0; i <= k; i++){
		int q = p2i(pi(k, i));
		ll tmp = forbidden | hate[q];
		if((tmp >> q) & 1) continue;
		policy.pb(i);
		ret += bt(k + 1, tmp);
		policy.pop_back();
	}
	
	return ret;
}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	scanf("%d %d %d", &n, &m, &K);
	for(int e = 0; e < m; e ++){
		scanf("%d %d %d", fr + e, to + e, cost + e);
		E[fr[e]].pb(e);
	}
	
	for(int u = 1; u <= n; u++) {
		sort(all(E[u]), [](const int & a, const int & b){
			return cost[a] < cost[b];
		});
		for(int k = 0; k < sz(E[u]); k++){
			int e = E[u][k], v = to[e];
			parent_edges[v].emplace_back(sz(E[u]) - 1, k);
		}
	}

	vi freq(55);
	for(int u = 1; u <= n; u++){
		fill(all(freq), 0);
		for(auto p : parent_edges[u]){
			freq[p2i(p)]++;
		}
		ll msk = 0;
		loop(i, sz(freq)) if(freq[i]) {
			msk |= 1LL << i;
		}
		loop(i, sz(freq)) if(freq[i]){
			ll tmp = msk;
			if(freq[i] == 1) {
				tmp ^= 1LL << i;
			}
			hate[i] |= tmp;
		}
	}
	
/*	loop(i, 55) if(hate[i]){
		cerr << i2p(i) << ": ";
		loop(j, 55) if((hate[i] >> j) & 1) {
			cerr << i2p(j) ;
		}
		cerr << endl;
	}
*/		
	cout << bt(0, 0) << endl;
	return 0;
}
