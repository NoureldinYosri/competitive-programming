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


const int MAX = 1000*1000 + 10;
vi G[MAX ];
int A[MAX ],n;
int W[MAX],id[MAX];
int fr[MAX],to[MAX],C[MAX],ord[MAX],m;

int find(int a) {
	return id[a] = (a == id[a]) ? a : find(id[a]);
}

ll join(int a,int b) {
	a = find(a),b = find(b);
	if(a == b) return 0;
	if(W[a] < W[b]) swap(a,b);
	ll ret = W[a] * 1LL * W[b];
	W[a] += W[b];
	id[b] = a;
	return ret;
}

int main(){
	#ifdef HOME
		freopen("in.in", "r", stdin);
	#endif
	scanf("%d",&n);
	range(i,1,n) scanf("%d",A + i);

	loop(e,n-1) {
		int a,b; scanf("%d %d",&a,&b);
		G[a].pb(b);
		G[b].pb(a);
	}

	ll ans = 0;

	range(u,1,n) for(int v : G[u]) if(u < v) {
		fr[m] = u;
		to[m] = v;
		C[m] = max(A[u],A[v]);
		ord[m] = m;
		m++;
	}
	sort(ord,ord + m,[](const int a,const int & b) {
		return C[a] < C[b];
	});
	range(i,1,n) id[i] = i,W[i] = 1;
	loop(i,m){
		int e = ord[i];
		ans += join(fr[e],to[e]) * C[e];
	}

	m = 0;
	range(u,1,n) for(int v : G[u]) if(u < v) {
		fr[m] = u;
		to[m] = v;
		C[m] = min(A[u],A[v]);
		ord[m] = m;
		m++;
	}
	sort(ord,ord + m,[](const int a,const int & b) {
		return C[a] > C[b];
	});
	range(i,1,n) id[i] = i,W[i] = 1;
	loop(i,m){
		int e = ord[i];
		ans -= join(fr[e],to[e]) * C[e];
	}

	cout << ans << endl;

	return 0;
}
