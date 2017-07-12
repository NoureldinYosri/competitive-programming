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
#define pl pair<ll,ll>
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

const int MAX = 100000 + 10;
int cnt[MAX];
int A[MAX],n,k;
int keypoint[MAX];
vi IDX[MAX];
vi ST[MAX << 2];

void build(int node,int s,int e){
	if(s == e) {
		ST[node].pb(keypoint[s]);
		return;
	}
	int m = (s + e) >> 1,left = node << 1,right = left | 1;
	build(left,s,m);
	build(right,m+1,e);
	range(k,s,e) ST[node].pb(keypoint[k]);
	sort(all(ST[node]));
}

int query(int node,int s,int e,int l,int r,int x){
	if(l <= s && e <= r) return lower_bound(all(ST[node]),x) - ST[node].begin();
	int m = (s + e) >> 1,left = node << 1,right = left | 1;
	if(r <= m) return query(left,s,m,l,r,x);
	if(m < l) return query(right,m+1,e,l,r,x);
	return query(left,s,m,l,m,x) + query(right,m+1,e,m+1,r,x);
}

int main(){
	#ifndef ONLINE_JUDGE
		freopen("in.in", "r", stdin);
	#endif
	scanf("%d %d",&n,&k);
	range(i,1,n) {
		scanf("%d",A + i);
		IDX[A[i]].pb(i);
	}
	range(i,1,n){
		int j = lower_bound(all(IDX[A[i]]),i) - IDX[A[i]].begin();
		if(j + 1 <= k) keypoint[i] = 0;
		else keypoint[i] = IDX[A[i]][j - k];
	}
	build(1,1,n);
	int lst = 0;
	int m; scanf("%d",&m);
	while(m--){
		int l,r; scanf("%d %d",&l,&r);
		l = (l + lst)%n + 1;
		r = (r + lst)%n + 1;
		if(l > r) swap(l,r);
		lst = query(1,1,n,l,r,l);
		printf("%d\n",lst);
	}
	return 0;
}
