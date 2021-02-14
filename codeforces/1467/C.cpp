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

vi V[3];

ll work(int collector, int target, int bucket){
	ll ret = 0;
	for(int x : V[target]) ret += x;
	for(int x : V[bucket]) ret += x;
	for(int x : V[collector]) ret -= x;
	return ret;	
}

ll work(int target){
	ll ret = 0;
	loop(i, 3) {
		for(int x : V[i]) ret += x;
		if(i != target) ret -= 2*V[i][0];
	}
//	cerr << target << ": " << ret << endl;
	return ret;
}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	loop(i, 3){
		int n; scanf("%d", &n);
		V[i].resize(n);
	}
	loop(i, 3) {
		for(int & x : V[i]) scanf("%d", &x);
		sort(all(V[i]));
	}
	ll ans = LLONG_MIN;
	loop(i, 3) {
		ans = max(ans, work(i));
		loop(j, 3) if(i != j) ans = max(ans, work(i, j, 3 - i - j));
	}
	cout << ans << endl;
	return 0;
}
