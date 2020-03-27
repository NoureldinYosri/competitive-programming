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

const int mod = 1e9 + 7;
int add(int a, int b){
	a += b;
	if(a >= mod) a -= mod;
	if(a < 0) a += mod;
	return a;
}
int mul(int a, int b){
	return (a*(ll)b)%mod;
}
int powmod(int a, int p){
	if(!p) return 1;
	int b = 1;
	for(; p > 1; p >>= 1){
		if(p & 1) b = mul(a, b);
		a = mul(a, a);
	}
	return mul(a, b);
}
int inv(int x){
	return powmod(x, mod-2);
}


const int MAX = 1 << 22;
int p2[MAX];
int n, A[MAX];
int m;
int P[MAX], value[MAX], pos[MAX];
vector<pi> V;

void init(){
	p2[0] = 1;
	for(int i = 1;i < MAX; i++)
		p2[i] = add(p2[i-1], p2[i-1]);
}

struct node{
	int size, ans;
	int left, right;
	friend ostream& operator << (ostream & st, const node & u){
		st << "{" << u.ans << ", " << u.size << ", ";
		st << pi(u.left, u.right) << "}";
		return st;
	}
};

node merge(node L, node R){
	node ret;
	ret.size = L.size + R.size;
	ret.left = add(L.left, mul(p2[L.size], R.left));
	ret.right = add(mul(L.right, p2[R.size]), R.right);
	ret.ans = add(mul(L.ans, p2[R.size]), mul(p2[L.size], R.ans));
	ret.ans = add(ret.ans, mul(L.left, R.right));
	return ret;
}

node ST[MAX];

void update(int cur, int s, int e, int p, int v){
	if(s == e){
		ST[cur].size = v > 0;
		ST[cur].ans = 0;
		ST[cur].left = ST[cur].right = v * (v > 0);
		return;
	}
	int m = (s + e) >> 1, left = 2*cur + 1, right = left + 1;
	if(p <= m) update(left, s, m, p, v);
	else update(right, m+1, e, p, v);
	ST[cur] = merge(ST[left], ST[right]);
}



int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	init();
	scanf("%d", &n);
	for(int i = 1;i <= n;i++) {
		scanf("%d", A + i);
		V.emplace_back(A[i], i);
	}
	scanf("%d", &m);
	loop(q, m) {
		scanf("%d %d", P + q, value + q);
		V.emplace_back(value[q], -q);
	}
	sort(all(V));
	
	int scaler = inv(p2[n]);
	for(int i = 1;i <= n;i ++) {
		int p = upper_bound(all(V), pi(A[i], i)) - V.begin();
		update(0, 1, sz(V), p, V[p-1].first);
		pos[i] = p;
	}
	printf("%d\n", mul(ST[0].ans, scaler));
	
	
	loop(q, m){
		int i = P[q], v = value[q];
		int & p = pos[i];
		update(0, 1, sz(V), p, -1);
		p = upper_bound(all(V), pi(v, -q)) - V.begin();
		update(0, 1, sz(V), p, V[p-1].first);
		printf("%d\n", mul(ST[0].ans, scaler));		
	}
	
	
	return 0;
}
