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
vi id, W;
vi fr, to, cost, ord;


void init(){
	id.resize(n);
	W.resize(n);
	
	fill(all(W), 1);
	iota(all(id), 0);
	
	ord.resize(m);
	iota(all(ord), 0);
	
	fr.resize(m);
	to.resize(m);
	cost.resize(m);
}

int find(int a){
	return id[a] = (a == id[a]) ? a : find(id[a]);
}
void join(int a, int b){
	a = find(a), b = find(b);
	if(a == b) return;
	if(W[a] < W[b]) swap(a, b);
	id[b] = a;
	W[a] += W[b];
}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	scanf("%d %d", &n, &m);
	init();
	loop(e, m) {
		int & a = fr[e];
		int & b = to[e];
		int & c = cost[e];
		scanf("%d %d %d", &a, &b, &c);
		a--, b--;
	}
	sort(all(ord), [](const int & a, const int & b){
		return cost[a] < cost[b];
	});
	int ans = 0;
	for(int e : ord) {
		int a = fr[e], b = to[e];
		if(find(a) != find(b)){
			ans = cost[e];
			join(a, b);
		}
	}
	cout << ans << endl;
	return 0;
}
