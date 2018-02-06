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

const int MAX = 100*1000,BITS = 17;
int A[MAX],n;
set<int> S[BITS];


ll brute_force(){
	int nxt [BITS];
	loop(i,BITS) nxt[i] = n;

	for(int j = 0;j < BITS;j++)
		S[j].insert(n);

	ll ret = 0;
	for(int i = n-1;i >= 0;i--) {
		for(int j = 0;j < BITS;j++)
			if(A[i] & (1 << j))
				ret += (nxt[j] - i) * (1LL << j);
			else{
				nxt[j] = i;
				S[j].insert(i);
			}
	}
	return ret;
}

ll getSum(int l,int r) {
	if(l > r) return 0;
	if(l == 0) return getSum(l+1,r);
	return r*(r + 1LL)/2 - l*(l - 1LL)/2;
}

ll getSum(int l,int r,int to) {
	return getSum(to - r,to - l);
}

void setToZero(int p,ll & ans) {
	for(int j = 0;j < BITS;j++)
		if(A[p] & (1 << j)) {
			auto it = S[j].lower_bound(p);
			int r = *it,l = -1;
			if(it != S[j].begin()) {
				--it;
				l = *it;
			}
			ans += (getSum(l+1,p,p) - getSum(l+1,p,r)) * (1 << j);
			S[j].insert(p);
		}
}

void update(int p,int v,ll & ans) {
	setToZero(p,ans);
	for(int j = 0;j < BITS;j++)
		if(v & (1 << j)) {
			S[j].erase(p);
			auto it = S[j].lower_bound(p);
			int r = *it,l = -1;
			if(it != S[j].begin()) {
				--it;
				l = *it;
			}
			ans += (getSum(l+1,p,r) - getSum(l+1,p-1,p)) * (1 << j);
		}
	A[p] = v;
}
int main(){
	#ifdef HOME
		freopen("in.in", "r", stdin);
	#endif
	int m;
	scanf("%d %d",&n,&m);
	loop(i,n) scanf("%d",A + i);
	ll ans = brute_force();
	while(m--) {
		int p,v; scanf("%d %d",&p,&v);
		--p;
		update(p,v,ans);
		printf("%lld\n",ans);
	}
	return 0;
}
