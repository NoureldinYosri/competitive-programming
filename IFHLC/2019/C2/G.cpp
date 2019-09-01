#ifdef DEBUG
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

const int mod = 99971;
int add(int a,int b) {
	a += b;
	if(a >= mod) a -= mod;
	return a;
}
int mul(int a,int b) {
	return (a*(ll)b)%mod;
}
int cube(int x) {
	return mul(x,mul(x,x));
}

const int MAXST = 1 << 19,MAX = 100* 1000 + 10,B = 48;

int cycle[MAXST][B],ST[MAXST];
int lazy[MAXST];
int A[MAX],n;


void push_up(int cur) {
	assert(!lazy[cur]);
	int left = 2*cur + 1,right = left + 1;
	loop(i,B) {
		int a = (i + lazy[left])%B;
		int b = (i + lazy[right])%B;
		cycle[cur][i] = add(cycle[left][a],cycle[right][b]);
	}
	ST[cur] = add(ST[left],ST[right]);
}

void build(int cur,int s,int e) {
	lazy[cur] = 0;
	if(s == e) {
		ST[cur] = cycle[cur][0] = A[s]%mod;
		loop(i,B-1) cycle[cur][i+1] = cube(cycle[cur][i]);
		return ;
	}
	int m = (s + e) >> 1,left = 2*cur + 1,right = left + 1;
	build(left,s,m);
	build(right,m+1,e);
	push_up(cur);
}


void update(int cur,int v) {
	lazy[cur] += v;
	lazy[cur] %= B;
	ST[cur] = cycle[cur][lazy[cur]];
}

void push_down(int cur) {
	if(!lazy[cur]) return;
	int left = 2*cur + 1,right = left + 1;
	update(left,lazy[cur]);
	update(right,lazy[cur]);
	lazy[cur] = 0;
}

void update(int cur,int s,int e,int l,int r) {
	if(l <= s && e <= r) return update(cur,1);
	push_down(cur);
	int m = (s + e) >> 1,left = 2*cur + 1,right = left + 1;
	if(r <= m) update(left,s,m,l,r);
	else if(m < l) update(right,m+1,e,l,r);
	else {
		update(left,s,m,l,m);
		update(right,m+1,e,m+1,r);
	}
	push_up(cur);
}
int query(int cur,int s,int e,int l,int r) {
//	cerr << s << " " << e << " " << l << " " << r << endl;
	if(l <= s && e <= r) return ST[cur];
	push_down(cur);
	push_up(cur);
	int m = (s + e) >> 1,left = 2*cur + 1,right = left + 1;
	if(r <= m) return query(left,s,m,l,r);
	if(m < l) return query(right,m+1,e,l,r);
	else {
		int a = query(left,s,m,l,m);
		int b = query(right,m+1,e,m+1,r);
		return add(a,b);
	}
}



int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	int T; scanf("%d",&T);
	while(T--) {
		int m; scanf("%d %d",&n,&m);
		for(int i = 1;i <= n;i++) scanf("%d",A + i);
		build(0,1,n);
		while(m--) {
			int t,l,r; scanf("%d %d %d",&t,&l,&r);
			if(t == 1) update(0,1,n,l,r);
			else printf("%d\n",query(0,1,n,l,r));
		}
	}
	return 0;
}

#endif
