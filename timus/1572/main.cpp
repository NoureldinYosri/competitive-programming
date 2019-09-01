#ifdef ACTIVE
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
#define tc() int T; scanf("%d",&T); for(int t = 1;t <= T;t++)
using namespace std;



pi big(int t,int s) {
	if(t == 1) return mp(4*s*s,1);
	else if(t == 2) return mp(2*s*s,1);
	else return mp(s*s,1);
}

pi small(int t,int s) {
	if(t == 1) return mp(4*s*s,1);
	else if(t == 2) return mp(s*s,1);
	else return mp(3*s*s,4);
}

auto cmp = [](const pi & x,const pi & L) {
	return x.first*L.second <= L.first*x.second;
};

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	int T,S; cin >> T >> S;
	int n; cin >>n ;
	int ans = 0;
	pi L = big(T,S);
	while(n--) {
		int t,s; cin >> t >> s;
		ans += cmp(small(t,s),L);
	}
	cout << ans << endl;
	return 0;
}
#endif
