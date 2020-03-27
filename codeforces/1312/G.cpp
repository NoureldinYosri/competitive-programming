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

const int MAXN = 1000*1000 + 10;
map<char, int> trie[MAXN];
int n;
int A[MAXN], m;
int ans[MAXN];
int ST[2 << 20];
int LA[2 << 20];
bool color[MAXN];

void build(int cur, int s, int e){
	if(s == e){
		ST[cur] = (1 << 29) * (s != 0);
		return ;
	}
	int m = (s + e) >> 1, left = 2*cur + 1, right = left + 1;
	build(left, s, m);
	build(right, m+1, e);
	ST[cur] = min(ST[left], ST[right]);
}

void add(int cur, int v){
	ST[cur] += v;
	LA[cur] += v;
}


void push(int cur){
	if(!LA[cur]) return;
	int left = 2*cur + 1, right = left + 1;
	add(left, LA[cur]);
	add(right, LA[cur]);
	LA[cur] = 0;
}

void update_set(int cur, int s, int e, int p, int v){
	if(s == e){
		ST[cur] = min(v, ST[cur]);
		return;
	}
	push(cur);
	int m = (s + e) >> 1, left = 2*cur + 1, right = left + 1;
	if(p <= m) update_set(left, s, m, p, v);
	else update_set(right, m+1, e, p, v);
	ST[cur] = min(ST[left], ST[right]);	
} 

void update(int cur, int s, int e, int l, int r, int v){
	if(l <= s && e <= r) return add(cur, v);
	push(cur);
	int m = (s + e) >> 1, left = 2*cur + 1, right = left + 1;
	if(r <= m) update(left, s, m, l, r, v);
	else if(m < l) update(right, m+1, e, l, r, v);
	else {
		update(left, s, m, l, m, v);
		update(right, m+1, e, m+1, r, v);
	}
	ST[cur] = min(ST[left], ST[right]);		
}

int query(int cur, int s, int e, int l, int r){
	if(l <= s && e <= r) return ST[cur];
	push(cur);
	int m = (s + e) >> 1, left = 2*cur + 1, right = left + 1;
	if(r <= m) return query(left, s, m, l, r);
	else if(m < l) return query(right, m+1, e, l, r);
	else return min(query(left, s, m, l, m),
						query(right, m+1, e, m+1, r));
}

void dfs(int u, int d){
	if(d && color[u]) update(0, 0, n, 0, d-1, 1);
	ans[u] = d ? min(query(0, 0, n, 0, d-1), d) : 0;
	update_set(0, 0, n, d, ans[u]);
	cout << u << " " << ans[u] << endl;
	for(auto p : trie[u])
		dfs(p.second, d+1);
}


int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	scanf("%d", &n);
	for(int i = 1; i <= n;i ++){
		int p; char c;
		scanf("%d %c", &p, &c);
		trie[p][c] = i;
		cerr << p << " " << i << " " << c << endl;
	}
	scanf("%d", &m);
	loop(i, m) {
		scanf("%d", A + i);
		color[A[i]] = 1;
	}
	build(0, 0, n);
	dfs(0, 0);
	loop(i, m) printf("%d\n", ans[A[i]]);
	
	return 0;
}
