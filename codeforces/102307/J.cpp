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
#define tc() int T; scanf("%d",&T); for(int t = 1;t <= T;t++)
using namespace std;


struct node{
	ll min_val,sum,lazy,siz;
	bool is_zero;
	friend ostream& operator << (ostream & st,const node & u) {
		st << "(" << u.min_val << ", " << u.sum << ", " << u.lazy << ", " << u.is_zero << ")";
		return st;
	}
};
const ll oo = 1LL << 60;
const int MAX = 100*1000 + 10,MAXST = 1 << 20;
int H[MAX],n;
node ST[MAXST];

void push_up(int cur) {
	int left = 2*cur + 1,right = left + 1;
	ST[cur].sum = ST[left].sum + ST[right].sum;
	ST[cur].lazy = 0;
	ST[cur].min_val = min(ST[left].min_val,ST[right].min_val);
	ST[cur].is_zero = ST[left].is_zero && ST[right].is_zero;
	ST[cur].siz = ST[left].siz + ST[right].siz;
}

void build(int cur,int s,int e) {
	if(s == e) {
		ST[cur].min_val = H[s];
		ST[cur].lazy = 0;
		ST[cur].siz = 1;
		ST[cur].sum = H[s];
		ST[cur].is_zero = H[s] == 0;
		if(ST[cur].is_zero) ST[cur].min_val = oo;
		return ;
	}
	int m = (s+e) >> 1,left = 2*cur + 1,right = left + 1;
	build(left,s,m);
	build(right,m+1,e);
	push_up(cur);
}

void push_down(int ,int,int);

void update(int cur,int s,int e,ll v) {
	if(ST[cur].is_zero) return;
	ST[cur].sum -= v*ST[cur].siz;
	ST[cur].min_val -= v;
	ST[cur].lazy += v;
	if(ST[cur].min_val < 0) {
		if(s == e) {
			ST[cur].sum = 0;
			ST[cur].min_val = oo;
			ST[cur].lazy = 0;
			ST[cur].is_zero = 1;
			ST[cur].siz = 0;
		}
		else {
			push_down(cur,s,e);
			push_up(cur);
		}
	}
//	cout << s << " " << e << " " << ST[cur] << endl;
	assert(ST[cur].sum >= 0);
	if(ST[cur].is_zero) {
		assert(ST[cur].sum == 0);
		assert(ST[cur].min_val == oo);
	}
}

void push_down(int cur,int s,int e) {
	if(!ST[cur].lazy) return;
	if(ST[cur].is_zero) return;
	int m = (s+e) >> 1,left = 2*cur + 1,right = left + 1;
	update(left,s,m,ST[cur].lazy);
	update(right,m+1,e,ST[cur].lazy);
	push_up(cur);
}


void update(int cur,int s,int e,int l,int r,int v) {
	if(ST[cur].is_zero) return;
	if(l <= s && e <= r) return update(cur,s,e,v);
	push_down(cur,s,e);
	int m = (s+e) >> 1,left = 2*cur + 1,right = left + 1;
	if(r <= m) update(left,s,m,l,r,v);
	else if(m < l) update(right,m+1,e,l,r,v);
	else {
		update(left,s,m,l,m,v);
		update(right,m+1,e,m+1,r,v);
	}
	push_up(cur);
}

ll query(int cur,int s,int e,int l,int r) {
	if(ST[cur].is_zero) return 0;
	if(l <= s && e <= r) return ST[cur].sum;
	push_down(cur,s,e);
	int m = (s+e) >> 1,left = 2*cur + 1,right = left + 1;
	if(r <= m)return query(left,s,m,l,r);
	else if(m < l) return query(right,m+1,e,l,r);
	else return query(left,s,m,l,m) + query(right,m+1,e,m+1,r);
}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	int Q;
	scanf("%d %d",&n,&Q);
	for(int i = 1;i <= n;i++)scanf("%d",H + i);
	build(0,1,n);
	vector<pi> aux;
	while(Q--) {
		int t,l,r;
		scanf("%d %d %d",&t,&l,&r);
		aux.clear();
		if(l <= r) aux.emplace_back(l,r);
		else {
			aux.emplace_back(l,n);
			aux.emplace_back(1,r);
		}
		if(t == 1) {
			ll ans = 0;
			for(auto p : aux)
				ans += query(0,1,n,p.first,p.second);
			printf("%lld\n",ans);
		}
		else {
			int s; scanf("%d",&s);
			for(auto p : aux)
				update(0,1,n,p.first,p.second,s);
		}
	}
	return 0;
}
