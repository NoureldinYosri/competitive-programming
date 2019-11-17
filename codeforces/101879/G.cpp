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
#define tc() int T; scanf("%d",&T); for(int t = 1;t <= T;t++)
using namespace std;



const int MAXA = 1000000000;
const int MAX = 300*1000 + 10;

int L[MAX],R[MAX];
pi ST[1 << 20];

pi merge(pi a,pi b) {
	return pi(max(a.first,b.first),min(a.second,b.second));
}

void build(int cur,int s,int e) {
	if(s == e) {
		ST[cur] = pi(L[s],R[s]);
		return ;
	}
	int m = (s + e) >> 1,left = 2*cur + 1,right = left+1;
	build(left,s,m);
	build(right,m+1,e);
	ST[cur] = merge(ST[left],ST[right]);
}

void update(int cur,int s,int e,int p,pi v) {
	if(s == e) {
		ST[cur] = v;
		return;
	}
	int m = (s + e) >> 1,left = 2*cur + 1,right = left+1;
	if(p <= m) update(left,s,m,p,v);
	else update(right,m+1,e,p,v);
	ST[cur] = merge(ST[left],ST[right]);
}

pi query(int cur,int s,int e,int l,int r) {
	if(l <= s && e <= r) return ST[cur];
	int m = (s + e) >> 1,left = 2*cur + 1,right = left+1;
	if(r <= m) return query(left,s,m,l,r);
	if(m < l) return query(right,m+1,e,l,r);
	return merge(query(left,s,m,l,m),query(right,m+1,e,m+1,r));
}


int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	int n,m; scanf("%d %d",&n,&m);
	for(int i = 0;i < n;i++) {
		int l,r; scanf("%d %d",&l,&r);
		L[i] = l;
		R[i] = r;
	}
	build(0,0,n-1);
	loop(q,m) {
		char c;
		scanf(" %c",&c);
		if(c == '?') {
			int l,r; scanf("%d %d",&l,&r);
			l--,r--;
			pi res = query(0,0,n-1,l,r);
			printf("%d\n",max(0,res.second-res.first+1));
		}
		else {
			int i; scanf("%d",&i); i--;
			int l,r; scanf("%d %d",&l,&r);
			update(0,0,n-1,i,pi(l,r));
		}
	}
	return 0;
}
#endif
