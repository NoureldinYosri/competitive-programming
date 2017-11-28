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

typedef pair<ll,ll> pl;
const int MAXN = 1000*1000 + 10,MAXH = 1000*1000*10 + 10;
int L[MAXN],R[MAXN],C[MAXN],parent[MAXN],n;
ll pref[MAXN];
vector<pl> T[MAXN];


void merge(vector<pl> & A,vector<pl> & B,vector<pl> & C) {
	int i = 0,j = 0;
	C.reserve(sz(A) + sz(B));
	while(i < sz(A) && j < sz(B)){
		if(A[i].xx < B[j].xx) C.pb(A[i++]);
		else C.pb(B[j++]);
	}
	while(i < sz(A)) C.pb(A[i++]);
	while(j < sz(B)) C.pb(B[j++]);
	ll sum = 0;
	for(auto & p : C){
		sum += p.xx;
		p.yy = sum;
	}
}
vector<pl>& build(int node){
	if(node > n) return T[0];
	vector<pl> &A = build(2*node);
	vector<pl> &B = build(2*node+1);
	T[node].reserve(sz(A) + sz(B) + 1);
	T[node].pb(mp(pref[node],pref[node]));
	merge(A,B,T[node]);
	return T[node];
}

ll query(vector<pl> & V,ll target) {
	auto p = lower_bound(all(V),mp(target,0LL));
	if(p == V.begin()) return 0;
	--p;
	int cnt = p - V.begin() + 1;
	ll ret = target*cnt - p->yy;
	assert(ret >= 0);
	return ret;
}


ll solve(int u,int H) {
	ll ret = query(T[u],H+pref[u]);


	int rem = H;
	while(u > 1 && rem > C[u]) {
		int p = u/2;
		rem -= C[u];
		ll tmp = rem;
		if(u & 1) {
			int l = L[p];
			assert(l == u-1);
			tmp += query(T[l],rem - C[l] + pref[l]);
		}
		else {
			int r = R[p];
			if(r)
				tmp += query(T[r],rem - C[r] + pref[r]);
		}
		ret += tmp;
		u = p;
	}
	return ret;
}

int main(){
	#ifdef HOME
		freopen("in.in", "r", stdin);
	#endif
	int m; scanf("%d %d",&n,&m);
	for(int e = 1;e < n;e++) {
		int p = (e + 1)/2,to = e + 1;
		if(to & 1) R[p] = to;
		else L[p] = to;
		scanf("%d",C + to);
		parent[to] = p;
		pref[to] = pref[p] + C[to];
	}



	build(1);

	loop(i,m){
		int u ,H; scanf("%d %d",&u,&H);
		printf("%lld\n",solve(u,H));
	}
	return 0;
}
