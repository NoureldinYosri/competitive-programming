#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define range(i,a,b) for(int i = (a);i <= (b);i++)
#define all(A) A.begin(),A.end()
#define pb push_back
#define mp make_pair
#define sz(A) ((int)A.size())
#define vi vector<int>
#define vl vector<long long>
#define vd vector<double>
#define vp vector<pair<int,int> >
#define ll long long
#define pi pair<int,int>
#define popcnt(x) __builtin_popcountll(x)
#define LSOne(x) ((x) & (-(x)))
#define xx first
#define yy second
#define PQ priority_queue
#define print(A,t) cerr << #A << ": "; copy(all(A),ostream_iterator<t>(cerr," " )); cerr << endl
#define prp(p) cerr << "(" << (p).first << " ," << (p).second << ")";
#define prArr(A,n,t)  cerr << #A << ": "; copy(A,A + n,ostream_iterator<t>(cerr," " )); cerr << endl
#define PRESTDIO() cin.tie(0),cerr.tie(0),ios_base::sync_with_stdio(0)
#define what_is(x) cerr << #x << " is " << x << endl
#define bit_lg(x) (assert(x > 0),__builtin_ffsll(x) - 1)
const double PI = acos(-1);
using namespace std;


int N,Q;
ll cnt,pref,len;
vl L;
ll BIT[1 << 20];
unordered_map<ll,unordered_map<int,ll > > dp;

void add(int pos,ll val) {
	for(;pos <= N;pos += LSOne(pos)) BIT[pos] += val;
}

ll get(int pos) {
	ll ret = 0;
	for(;pos;pos ^= LSOne(pos)) ret += BIT[pos];
	return ret;
}

unordered_map<int,ll> solve(ll len) {
	if(len == 0) return unordered_map<int,ll>();
	if(dp.find(len) != dp.end()) return dp[len];
	auto p = lower_bound(all(L),len) - L.begin();
	assert(p > 0);
	--p;
	unordered_map<int,ll> ret;
	if(p != 0) {
		ret = solve(len%L[p]);
		ret[-p] += len/L[p];
	}
	else ret[len] = 1;
	dp[len] = ret;
	return ret;
}


void recon(ll len,ll coef) {
	map<ll,ll> M;
	M[len] = 1;
	while(!M.empty()){
		len = M.rbegin()->xx;
		coef = M[len];
		M.erase(len);
		for(auto p : solve(len))
			if(p.xx < 0)
				M[L[-p.xx]] += coef*p.yy;
			else {
				add(1,coef*p.yy);
				add(p.xx+1,-coef*p.yy);
			}
	}
}
int main(){
	#ifdef HOME
		freopen("in.in", "r", stdin);
	#endif
	scanf("%d %d",&N,&Q);
	L.pb(0);
	L.pb(N);
	while(Q--) {
		ll q; scanf("%lld",&q);
		while(!L.empty() && L.back() >= q) L.pop_back();
		L.pb(q);
	}

	ll len = L.back();
	recon(len,1);
	range(i,1,N) printf("%lld\n",get(i));
	return 0;
}
