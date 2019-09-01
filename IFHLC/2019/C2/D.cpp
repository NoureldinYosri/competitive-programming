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
using namespace std;

const int MAX = 200*1000 + 10;
int fr[MAX],to[MAX];
int n,Q,m;
int ctr[MAX];
int BIT[MAX];
pi E[MAX];
int ans[MAX];
int L[MAX],R[MAX],ord[MAX];

void add(int p,int v) {
	for(;p < MAX;p += LSOne(p))
		BIT[p] += v;
}
int get(int p){
	int ret = 0;
	for(;p;p ^= LSOne(p))
		ret += BIT[p];
	return ret;
}



void tc(){
	scanf("%d %d",&n,&Q);
	m = 0;
	memset(BIT,0,sizeof BIT);
	for(int i = 1;i <= n;i++) ctr[i] = 0;
	loop(e,n-1){
		scanf("%d %d",fr + e,to + e);
		if(fr[e] < to[e]) swap(fr[e],to[e]);
		E[m++] = pi(fr[e],to[e]);
		ctr[fr[e]]++;
	}
	sort(E,E + m);
	loop(q,Q) {
		int l,r; scanf("%d %d",&l,&r);
		L[q] = l;
		R[q] = r;
		ord[q] = q;
		ans[q] = r-l+1;
	}
	sort(ord,ord + Q,[](const int & a,const int & b) {
		return R[a] < R[b];
	});
	int i = 0,tot = 0;
	for(int j = 0;j < Q;j++) {
		int q = ord[j];
		while(i < m && E[i].first <= R[q]) {
			tot++;
			int p = E[i].second;
			add(p,1);
			i++;
		}
		ans[q] -= tot - get(L[q] - 1);
	}
	loop(q,Q) printf("%d\n",ans[q]);
}



int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	int T; scanf("%d",&T);
	while(T--) {
		tc();
	}
	return 0;
}
#endif
