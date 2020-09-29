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

const int MAXA = 1000*1000;
int n, m;
vi BIT(1 << 20, 0);
vector<pair<pi, pi>> events;

void add(int p, int v){
	for(++p; p < sz(BIT); p += LSOne(p)){
		BIT[p] += v;
	}
}
int get(int p){
	int ret = 0;
	for(++p; p; p ^= LSOne(p))
		ret += BIT[p];
	return ret;
}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	ll ans = 1;
	scanf("%d %d", &n, &m);
	loop(i, n){
		int y, l, r; scanf("%d %d %d", &y, &l, &r);
		events.emplace_back(pi(l, -1), pi(y, 0));
		events.emplace_back(pi(r, 1), pi(y, 0));
		if(l == 0 && r == MAXA) ans++;
	}
	loop(i, m){
		int x, s, e; scanf("%d %d %d", &x, &s, &e);
		events.emplace_back(pi(x, 0), pi(s, e)); 
	}
	sort(all(events));
	
	add(0, 1);
	add(MAXA, 1);
	
	for(auto [q, inf] : events){
		auto [x, t] = q;
		auto [s, e] = inf;
		if(t) add(s, -t);
		else {
			ans += get(e) - get(s - 1) - 1;
		}
	}
	cout << ans << endl;
	return 0;
}
