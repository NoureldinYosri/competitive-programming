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


const int MAX = 500*1000 + 10;
struct vertex{
	ll cnt;
	int l,r;
	int s,e;
	vertex(){
		cnt = s = e = 0;
		l = r = -1;
	}
	vertex(int pos,int x) {
		s = e = pos;
		cnt = 0;
		l = r = -1;
		if(x) {
			l = r = pos;
			cnt = 1;
		}
	}
	friend ostream& operator << (ostream & st,const vertex & v) {
		st << "([" << v.s << ", " << v.e << "] l=" << v.l << " r=" << v.r << " cnt=" << v.cnt << ")";
		return st;
	}
};

vertex merge(vertex A,vertex B,bool debug = 0) {
	vertex ret;
	ret.s = A.s;
	ret.e = B.e;

	if(A.l == -1) ret.l = B.l;
	else ret.l = A.l;
	if(B.r == -1) ret.r = A.r;
	else ret.r = B.r;

	ret.cnt = A.cnt + B.cnt;

	int need = 0;
	if(A.r == -1) need = A.e - A.s + 1;
	else need = A.e - A.r;

	int dontNeed = A.e - A.s + 1 - need;
	ret.cnt += dontNeed * (B.e - B.s + 1LL);

	if(B.l != -1)
		ret.cnt += need * (B.e - B.l + 1LL);

	if(debug) cerr << A << " + " << B << " = " << ret << endl;
	return ret;
}

int N,Q,L,R;
vertex ST[2][MAX << 2];
int Th[2];

void build(int node,int s,int e) {
	if(s == e) {
		loop(i,2) ST[i][node] = vertex(s,0 >= Th[i]);
		return;
	}
	int m = (s + e) >> 1,left = node << 1,right = left | 1;
	build(left,s,m);
	build(right,m+1,e);
	loop(i,2) ST[i][node] = merge(ST[i][left],ST[i][right]);
}

void update(int node,int s,int e,int pos,int val) {
	if(s == e) {
		loop(i,2) ST[i][node] = vertex(s,val >= Th[i]);
//		loop(i,2) cerr << ST[i][node] << " " ;
//		cerr << endl;
		return;
	}
	int m = (s + e) >> 1,left = node << 1,right = left | 1;
	if(pos <= m) update(left,s,m,pos,val);
	else update(right,m+1,e,pos,val);
	loop(i,2) ST[i][node] = merge(ST[i][left],ST[i][right]);
//	loop(i,2) cerr << ST[i][node] << " " ;
//	cerr << endl;
}

pair<vertex,vertex> query(int node,int s,int e,int l,int r) {
	if(l <= s && e <= r) return mp(ST[0][node],ST[1][node]);
	int m = (s + e) >> 1,left = node << 1,right = left | 1;
	if(r <= m) return query(left,s,m,l,r);
	if(m < l) return query(right,m+1,e,l,r);
	auto A = query(left,s,m,l,m),B = query(right,m+1,e,m+1,r);
	auto res = mp(merge(A.xx,B.xx),merge(A.yy,B.yy));
	return res;
}

int main(){
	#ifdef HOME
		freopen("in.in", "r", stdin);
	#endif
	scanf("%d %d %d %d",&N,&Q,&L,&R);
	Th[0] = L;
	Th[1] = R + 1;
	build(1,1,N);

	while(Q--) {
		int type,a,b;
		scanf("%d %d %d",&type,&a,&b);
		if(type == 1) update(1,1,N,a,b);
		else {
			auto res = query(1,1,N,a,b);
			printf("%lld\n",res.xx.cnt - res.yy.cnt);
		}
	}
	return 0;
}
