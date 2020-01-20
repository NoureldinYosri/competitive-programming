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


pair<bool,pi> read(){
	int n; scanf("%d",&n);
	int mx = INT_MIN, mn = INT_MAX;
	bool f = 0;
	loop(i,n){
		int x; scanf("%d",&x);
		if(i && x > mn) f = 1;
		mn = min(mn, x);
		mx = max(mx, x);
	}
	return make_pair(f, pi(mn, mx));
}



vector<pi> V;

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	int n; scanf("%d",&n);
	ll ans = 0;
	ll m = 0;
	loop(i,n){
		auto info = read();
		if(info.first) m++;
		else V.push_back(info.second);
	}
	ans += 2 * m * sz(V) + m*m;
	sort(all(V));
	for(auto p : V){
		int mx = p.second;
		auto E = upper_bound(all(V), pi(mx,INT_MIN)); 
		ans += E - V.begin();
	}

	cout << ans << endl;
	return 0;
}
