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


int n,R;
vp P[2];


bool classify(pi p) {
	if(p.second > 0) return 1;
	if(p.second < 0) return 0;
	assert(p.first);
	return p.first > 0;
}


ll cross(pi a,pi b) {
	return a.first*(ll)b.second - a.second*(ll)b.first;
}

ll norm(pi a) {
	return a.first*(ll)a.first + a.second*(ll)a.second;
}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	pi O;
	scanf("%d %d %d %d",&O.first,&O.second,&R,&n);
	ll R2 = R*(ll)R;
	loop(i,n){
		pi p; scanf("%d %d",&p.first,&p.second);
		p.first -= O.first;
		p.second -= O.second;
		P[classify(p)].push_back(p);
//		cout << p << endl;
	}
	int ans = 0;
	auto cmp = [](const pi & a,const pi & b) {
		ll s = cross(a,b);
		if(s) return s > 0;
		return norm(a) < norm(b);
	};
	loop(i,2){
		sort(all(P[i]),cmp);
		pi lst; bool isFirst = 1;
		for(pi p : P[i]) {
			if(isFirst || cross(lst,p)) ans += norm(p) <= R2;
			lst = p;
			isFirst = 0;
		}
	}
	cout << ans << endl;
	return 0;
}
#endif
