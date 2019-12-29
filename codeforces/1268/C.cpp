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


const int MAX = 200*1000 + 10;
int BIT[MAX];
int A[MAX],n;
int I[MAX];

void add(int p,int v){
	for(;p <= n;p += LSOne(p))
		BIT[p] += v;
}

int get(int p){
	int ret = 0;
	for(;p;p ^= LSOne(p))
		ret += BIT[p];
	return ret;
}

struct node{
	int pivot_cnt;
	int siz;
	ll left_cost,right_cost;
};

node ST[1 << 21];

node merge(node L,node R){
	node ret;
	ret.pivot_cnt = L.pivot_cnt + R.pivot_cnt;
	ret.siz = L.siz + R.siz;
	ret.left_cost = L.left_cost + R.left_cost + L.pivot_cnt*(ll)R.siz;
	ret.right_cost = L.right_cost + R.right_cost + L.siz*(ll)R.pivot_cnt;
	return ret;
}

void build(int cur,int s,int e){
	if(s == e){
		ST[cur].siz = s >= 1 && e <= n;
		return;
	}
	int m = (s + e) >> 1,left = 2*cur + 1,right = left + 1;
	build(left,s,m);
	build(right,m+1,e);
	ST[cur] = merge(ST[left],ST[right]);
}

void update(int cur,int s,int e,int p){
	if(s == e){
		ST[cur].pivot_cnt = 1;
		ST[cur].siz = 0;
		ST[cur].left_cost = ST[cur].right_cost = 0;
		return;
	}
	int m = (s + e) >> 1,left = 2*cur + 1,right = left + 1;
	if(p <= m) update(left,s,m,p);
	else update(right,m+1,e,p);
	ST[cur] = merge(ST[left],ST[right]);	
}

node query(int cur,int s,int e,int l,int r){
	if(l <= s && e <= r) return ST[cur];
	int m = (s + e) >> 1,left = 2*cur + 1,right = left + 1;
	if(r <= m) return query(left,s,m,l,r);
	if(m < l) return query(right,m+1,e,l,r);
	return merge(query(left,s,m,l,m), query(right,m+1,e,m+1,r));
}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	scanf("%d",&n);
	for(int i = 1;i <= n;i++) {
		scanf("%d",A + i);
		I[A[i]] = i;
	}
	set<int> S;
	S.insert(0);
	S.insert(n+1);
	
	auto mid = S.begin();
	
	build(0,0,n+1);
	
	ll inversion = 0;
	for(int x = 1;x <= n;x++){
		int i = I[x];
		int left_cnt = get(i),right_cnt = x-1-left_cnt;
		
		inversion += right_cnt;
		
		update(0,0,n+1,i);
		
		add(i,1);
		S.insert(i);
		
		while(2*get(*mid) > x) mid--;
		while(2*get(*mid) <= x) mid++;

		assert(*mid >= 1);
		assert(*mid <= n);
		ll work = query(0,0,n+1,1,*mid).left_cost;
		work += query(0,0,n+1,*mid,n).right_cost;
		
		ll ans = inversion + work;
		printf("%lld ",ans);
	}
	
	puts("");

	return 0;
}
