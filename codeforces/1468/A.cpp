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

struct quanta{
	int val, flag;
	bool operator < (const quanta & q) const {
		if(val + flag == q.val + q.flag){
			return flag > q.flag;
		}
		return val + flag < q.val + q.flag;
	}	
	friend ostream& operator <<(ostream & st, const quanta & q){
		st << pi(q.val, q.flag);
		return st;
	}
};

const int MAXN = 500*1000 + 10, MAXST = 1 << 21;
quanta ST[MAXST];
int lazy[MAXST];
int S, E;
int A[MAXN], n;

void set_bit(int cur){
	lazy[cur] = 1;
	ST[cur].flag = 1;	
}

void push_down(int cur){
	if(!lazy[cur]) return;
	int left = 2*cur + 1, right = left + 1;
	set_bit(left);
	set_bit(right);
	lazy[cur] = 0;	
}

void push_up(int cur){
	int left = 2*cur + 1, right = left + 1;
	ST[cur] = max(ST[left], ST[right]);
}

void set_bit(int cur, int s, int e, int l, int r){
//	cerr << "set bit " << pi(s, e) << " " << pi(l, r) << endl;
	if(l <= s && e <= r) return set_bit(cur);
	push_down(cur);
	int m = (s + e) >> 1, left = 2*cur + 1, right = left + 1;
	if(r <= m) set_bit(left, s, m, l, r);
	else if(m < l) set_bit(right, m+1, e, l, r);
	else {
		set_bit(left, s, m, l, m);
		set_bit(right, m + 1, e, m + 1, r);
	}
	push_up(cur);
}

void set_val(int cur, int s, int e, int p, quanta v){
	if(s == e) {
		ST[cur] = max(ST[cur], v);
		return;
	}
	push_down(cur);
	int m = (s + e) >> 1, left = 2*cur + 1, right = left + 1;
	if(p <= m) set_val(left, s, m, p, v);
	else set_val(right, m+1, e, p, v);
	push_up(cur);
}

quanta query(int cur, int s, int e, int l, int r){
	if(l <= s && e <= r) {
//		cerr << "query " << pi(s, e) << " for " << pi(l, r) << ": " << ST[cur].val << " " << ST[cur].flag << endl;
		return ST[cur];
	}
	push_down(cur);
	int m = (s + e) >> 1, left = 2*cur + 1, right = left + 1;
	if(r <= m) return query(left, s, m, l, r);
	if(m < l)  return query(right, m+1, e, l, r);
	quanta a = query(left, s, m, l, m), b = query(right, m+1, e, m+1, r);
//	cerr << "\tFrom " << a << " " << b << " return " << max(a, b) << endl;
	return max(a, b);
}

void init(int cur, int s, int e){
	ST[cur] = quanta();
	lazy[cur] = 0;
	if(s == e) return;
	int m = (s + e) >> 1, left = 2*cur + 1, right = left + 1;
	init(left, s, m);
	init(right, m+1, e);
}

void tc(){
	scanf("%d", &n);
	loop(i, n) scanf("%d", A + i);
	S = 0;
	E = n;
	init(0, S, E);
	int ans = 0;
	loop(i, n){
		quanta q = query(0, S, E, 1, A[i]);
//		cerr << A[i] << ": " << q.val << " " << q.flag << endl;
		int val = q.val + q.flag + 1;
		ans = max(ans, val);
		set_val(0, S, E, A[i], quanta({val, 0}));
		set_bit(0, S, E, 0, A[i] - 1);
	}
	printf("%d\n", ans);
}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	int T; scanf("%d", &T);
	while(T--) tc();
	return 0;
}
