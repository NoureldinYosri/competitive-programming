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


vector<pair<int, pi> > E;
int n, m;

int id[111], W[111];
int find(int a){
	return id[a] = (a == id[a]) ? a : find(id[a]);
}
int join(int a, int b){
	a = find(a), b = find(b);
	if(a == b) return 0;
	if(W[a] < W[b]) swap(a, b);
	W[a] += W[b];
	id[b] = a;
	return 1;
}

void init(){
	for(int i = 1; i <= n;i++) id[i] = i, W[i] = 1;	
}

bool valid(int msk, int target){
	int cost = 0;
	init();
	loop(e, m) if((msk >> e) & 1){
		int a = E[e].second.first, b = E[e].second.second;
		if(join(a, b)) cost += E[e].first;
		else return 0;
	}
	assert(cost >= target);
	return cost == target;
}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	cin >> n >> m;
	loop(e, m){
		int a, b, c;
		scanf("%d %d %d", &a, &b, &c);
		E.emplace_back(c, pi(a, b));
	}
	sort(all(E));
	init();
	int cost = 0;
	for(auto e : E){
		int a = e.second.first, b = e.second.second;
		cost += e.first * join(a, b);
	}
	int ans = 0;
	for(int msk = 1; msk < (1 << m); msk++){
		if(popcnt(msk) != n-1) continue;
		ans += valid(msk, cost);
	}
	
	assert(ans);
	cout << ans << endl;
	return 0;
}
