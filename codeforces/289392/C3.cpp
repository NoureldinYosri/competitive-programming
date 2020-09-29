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

int n, m;
map<pi, int> enteryTime;
vp ST[1 << 20];
bool isQuestion[1 << 20];
vi id, W;
vector<pair<int*, int>> hist;

void rollback(int s){
	while(sz(hist) > s){
		auto [ptr, v] = hist.back(); hist.pop_back();
		*ptr = v;
	}
}
void replace(int *ptr, int v){
	hist.emplace_back(ptr, *ptr);
	*ptr = v;
}

int find(int a){
	if(id[a] == a) return a;
	replace(&id[a], find(id[a]));
	return id[a];
}

void join(int a, int b){
	a = find(a);
	b = find(b);
	if(a == b) return;
	replace(&n, n-1);
	if(W[a] < W[b]) swap(a, b);
	replace(&id[b], a);
	replace(&W[a], W[a] + W[b]);
}


void insert(int cur, int s, int e, int l, int r, pi E){
	if(l <= s && e <= r) {
		ST[cur].pb(E);
		return;
	}
	int m = (s + e) >> 1, left = 2*cur + 1, right = left + 1;
	if(r <= m) insert(left, s, m, l, r, E);
	else if(m < l) insert(right, m+1, e, l, r, E);
	else {
		insert(left, s, m, l, m, E);
		insert(right,m+1, e, m+1, r, E); 
	}
}


void dfs(int cur, int s, int e){
	int t = sz(hist);
	for(auto [a, b] : ST[cur]) join(a, b);
	if(s == e){
		if(isQuestion[s]) printf("%d\n", n);
	} else {
		int m = (s + e) >> 1, left = 2*cur + 1, right = left + 1;
		dfs(left, s, m);
		dfs(right, m+1, e);
	}
	rollback(t);
}


int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	scanf("%d %d", &n, &m);
	loop(q, m){
		char c; scanf(" %c", &c);
		if(c == '?') isQuestion[q] = true;
		else {
			int a, b; scanf("%d %d", &a, &b);
			a--, b--;
			if(a > b) swap(a, b);
			pi e(a, b);
			if(enteryTime.count(e)){
				assert(c == '-');
				int l = enteryTime[e];
				enteryTime.erase(e);
				insert(0, 0, m-1, l, q, e);
			} else {
				assert(c == '+');
				enteryTime[e] = q;
			}
		}
	}
	for(auto [e, l] : enteryTime){
		insert(0, 0, m-1, l, m-1, e);
	}
	id.resize(n);
	W.resize(n);
	fill(all(W), 1);
	iota(all(id), 0);
	if(m) dfs(0, 0, m-1);
	return 0;
}
