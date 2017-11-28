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

const int MAX = 100*1000 + 10;
ll pref[MAX];
int n,m,blkSize;
int L[MAX],R[MAX],id[MAX],ord[MAX],A[MAX];
ll ans[MAX],aux[MAX];
int val[MAX],up[MAX],down[MAX];
int cnt[MAX];

int main(){
	#ifdef HOME
		freopen("in.in", "r", stdin);
	#endif
	int k;
	scanf("%d %d",&n,&k);
	range(i,1,n){
		int t; scanf("%d",&t);
		if(t == 1) A[i] = 1;
		else A[i] = -1;
	}
	range(i,1,n){
		int t; scanf("%d",&t);
		A[i] = A[i] * t;
		pref[i] = pref[i - 1] + A[i];
	}

	copy(pref,pref + n + 1,aux);
	int N = n + 1;
	sort(aux,aux + n + 1);
	N = unique(aux,aux + N) - aux;
	for(int i = 0;i <= n;i++) {
		val[i] = upper_bound(aux,aux + N,pref[i]) - aux;
		ll t = pref[i] + k;
		if(binary_search(aux,aux + N,t))
			up[i] = upper_bound(aux,aux + N,t) - aux;
		t = pref[i] - k;
		if(binary_search(aux,aux + N,t))
			down[i] = upper_bound(aux,aux + N,t) - aux;
	}

	blkSize = sqrt(n);
	scanf("%d",&m);
	loop(i,m) {
		scanf("%d %d",L + i,R + i);
		L[i]--;
		id[i] = L[i]/blkSize;
		ord[i] = i;
	}

	sort(ord,ord + m,[](const int & a,const int & b) {
		return tie(id[a],R[a]) < tie(id[b],R[b]);
	});

	for(int q = 0,blk = 0;q < m;blk++) {
		int l = blk*blkSize,r = l-1;
		ll f = 0,v,u;
		for(;q < m && id[ord[q]] == blk;q++) {
			for(;r < R[ord[q]];r++) {
				v = val[r + 1];
				u = down[r + 1];
				f += cnt[u];
				cnt[v]++;
			}
			for(;L[ord[q]] < l;l--) {
				v = val[l - 1];
				u = up[l - 1];
				f += cnt[u];
				cnt[v]++;
			}
			for(;l < L[ord[q]];l++) {
				v = val[l];
				u = up[l];
				f -= cnt[u]-(k==0);
				cnt[v]--;
			}
			ans[ord[q]] = f;
		}
		for(;l <= r;l++)
			cnt[val[l]] = 0;
	}
	loop(i,m) printf("%lld\n",ans[i]);
	return 0;
}
