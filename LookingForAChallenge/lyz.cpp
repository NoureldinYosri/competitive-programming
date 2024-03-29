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


const int MAXN = 200*1000 + 10, MAXST = 1 << 20;
int n, d, k, m;
struct node{
	ll sum, pref, suff, mx;
};
node ST[MAXST];

node merge(node L, node R){
	node ret;
	ret.sum = L.sum + R.sum;
	ret.pref = max(L.pref, L.sum + R.pref);
	ret.suff = max(L.suff + R.sum, R.suff);
	ret.mx = max(L.mx, R.mx);
	ret.mx = max(ret.mx, L.suff + R.pref);
	ret.mx = max(ret.mx, max(ret.pref, ret.suff));
	return ret;
}

void build(int cur, int s, int e){
	if(s == e) {
		ST[cur].sum = ST[cur].mx = ST[cur].pref = ST[cur].suff = -k;
		return;
	}
	int m = (s + e) >> 1, left = 2*cur+1, right = left+1;
	build(left, s, m);
	build(right, m+1, e);
	ST[cur] = merge(ST[left], ST[right]);
}

void update(int cur, int s, int e, int p, int v){
	if(s == e){
		ll value =  ST[cur].sum + v;
		ST[cur].sum = ST[cur].mx = ST[cur].pref = ST[cur].suff = value;
		return;
	}
	int m = (s + e) >> 1, left = 2*cur+1, right = left+1;
	if(p <= m) update(left, s, m, p, v);
	else update(right, m+1, e, p, v);
	ST[cur] = merge(ST[left], ST[right]);	
}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	scanf("%d %d %d %d", &n, &m, &k, &d);
	build(0, 1, n);
	ll kd = k*(ll)d;
	while(m--){
		int r, x; scanf("%d %d", &r, &x);
		update(0, 1, n, r, x);
		puts((ST[0].mx > kd) ? "NIE" : "TAK");
	}
	return 0;
}
