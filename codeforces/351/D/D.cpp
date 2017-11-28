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
int A[MAX],prv[MAX],lst[MAX],n;
vi ST[MAX*4];
int T[2][MAX];
int L[MAX],R[MAX],ans[MAX];
vi Q[MAX];

void update(int p,int v,int *BIT) {
	for(;p <= n;p += LSOne(p)) BIT[p] += v;
}
int query(int p,int *BIT){
	int ret = 0;
	for(;p;p ^= LSOne(p)) ret += BIT[p];
	return ret;
}


void merge(vi & A,vi & B,vi & C){
	int i = 0,j = 0;
	C.reserve(sz(A) + sz(B));
	while(i < sz(A) && j < sz(B)){
		if(A[i] < B[j]) C.pb(A[i++]);
		else C.pb(B[j++]);
	}
	while(i < sz(A)) C.pb(A[i++]);
	while(j < sz(B)) C.pb(B[j++]);
}

void build(int node,int s,int e) {
	if(s == e) {
		ST[node].pb(prv[s]);
		return;
	}
	int m = (s + e) >> 1,left = node << 1,right = left | 1;
	build(left,s,m);
	build(right,m+1,e);
	merge(ST[left],ST[right],ST[node]);
}

int query(int node,int s,int e,int l,int r,int th) {
	if(l <= s && e <= r) return upper_bound(all(ST[node]),th) - ST[node].begin();
	int m = (s + e) >> 1,left = node << 1,right = left | 1;
	if(r <= m) return query(left,s,m,l,r,th);
	if(m < l) return query(right,m+1,e,l,r,th);
	return query(left,s,m,l,m,th) + query(right,m+1,e,m+1,r,th);
}

int main(){
	#ifdef HOME
		freopen("in.in", "r", stdin);
	#endif
	scanf("%d",&n);
	range(i,1,n) scanf("%d",A + i);

	range(i,1,n){
		int x = A[i];
		prv[i] = lst[x];
		lst[x] = i;
	}
	build(1,1,n);

	int m; scanf("%d",&m);
	loop(i,m){
		scanf("%d %d",L + i,R + i);
		ans[i] = query(1,1,n,L[i],R[i],L[i]-1) + 1;
		Q[R[i]].pb(i);
	}

	for(int r = 1;r <= n;r++) {
		int b = prv[r],a = prv[b],x = A[r];
		if(b == 0) {
			update(1,1,T[0]);
			update(r,1,T[1]);
			lst[x] = 1;
		}
		else if(a != 0 && b - a != r - b){
			update(lst[x],-1,T[0]);
			update(a+1,1,T[0]);
			lst[x] = a+1;

			update(b,-1,T[1]);
			update(r,1,T[1]);
		}
		else {
			update(b,-1,T[1]);
			update(r,1,T[1]);
		}
		for(int q : Q[r]){
			int A = query(L[q],T[0]) ,B = query(L[q]-1,T[1]),tmp = A - B;
			assert(tmp >= 0);
			ans[q] -= tmp > 0;
		}
	}
	loop(i,m) printf("%d\n",ans[i]);
	return 0;
}
