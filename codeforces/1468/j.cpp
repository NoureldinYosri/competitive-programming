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

vp zeros;
map<int, vp> class1, class2;
int n, m, k, N;
vi id, W;

void init(){
	if(sz(id) != n) {
		id.resize(n);
		W.resize(n);
	}
	N = n;
	fill(all(W), 1);
	iota(all(id), 0);
}

int find(int a){
	return id[a] = (a == id[a]) ? a : find(id[a]);
}
bool join(int a, int b){
	a = find(a), b = find(b);
	if(a == b) return false;
	if(W[a] < W[b]) swap(a, b);
	W[a] += W[b];
	id[b] = a;
	N--;
	return true;
}

ll solve(bool use){
	init();
	for(auto [a, b] : zeros) join(a, b);
	int tmp = 0;
	if(use && !class1.empty()){
		if(zeros.empty()) tmp = class1.begin()->first;
		for(auto & [c, E] : class1)
			for(auto [a, b] : E)
				join(a, b);
	}
	if(N == 1) {
		if(class2.empty()) return tmp;
		return min(tmp, class2.begin()->first);
	}
	ll ret = 0;
	for(auto & [c, E] : class2)
		for(auto [a, b] : E)
			ret += c * join(a, b);

	if(N != 1) ret = 1LL << 60;
	return ret;
}



void tc(){
	scanf("%d %d %d", &n, &m, &k);
	zeros.clear();
	class1.clear();
	class2.clear();
	loop(e, m){
		int a, b, c; scanf("%d %d %d", &a, &b, &c);
		a--, b--;
		if(c == k) zeros.emplace_back(a, b);
		else if(c < k){
			class1[k - c].emplace_back(a, b);
		} else {
			class2[c - k].emplace_back(a, b);
		}
	}
	printf("%lld\n", min(solve(false), solve(true)));
}



int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	int T; scanf("%d", &T);
	while(T--) tc();
	return 0;
}
