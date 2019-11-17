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


int n,Q;
pi P[2 << 10];

pi operator - (const pi & a,const pi & b){
	return pi(a.first-b.first,a.second-b.second);
}

pi canon(pi v) {
	if(v.first == 0) return pi(0,1);
	if(v.first < 0) v = pi(-v.first,-v.second);
	int g = __gcd(v.first,abs(v.second));
	v.first /= g;
	v.second /= g;
	return v;
}

struct Hash{
	ll operator () (const pi & p) const {
		return p.first * 1e9 + p.second;
	}
};

unordered_map<pi,int,Hash> cnt[2 << 10];

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	scanf("%d %d",&n,&Q);
	loop(i,n) scanf("%d %d",&P[i].first,&P[i].second);
	loop(j,n) loop(i,n){
		if(i == j) continue;
		pi v = P[i] - P[j];
		v = canon(v);
		cnt[j][v]++;
	}

	unordered_map<pi,int,Hash> aux;
	while(Q--) {
		pi p; scanf("%d %d",&p.first,&p.second);
		int ans = 0;
		aux.clear();
		loop(i,n) {
			pi u = p - P[i];
			pi v = pi(u.second,-u.first);
			u = canon(u);
			v = canon(v);

			int tmp = 0;

			if(aux.count(v)) tmp += aux[v];
			aux[u]++;

			if(cnt[i].count(v))
				tmp += cnt[i][v];
//			cout << p << " " << P[i] << ": " << tmp << endl;
			ans += tmp;
		}
		printf("%d\n",ans);
	}
	return 0;
}
#endif
