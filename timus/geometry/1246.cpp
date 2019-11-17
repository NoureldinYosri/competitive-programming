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

const int MAX = 200000;
pi I[MAX];
int n;
set<pi> CH;

ll cross(pi o,pi a,pi b) {
	a.first -= o.first,a.second -= o.second;
	b.first -= o.first,b.second -= o.second;
	return a.first*(ll)b.second - a.second*(ll)b.first;
}

pi getHull(vector<pi> & P) {
	vector<pi> H;
	for(pi p : P) {
		while(sz(H) > 1 && cross(H[sz(H)-2],H[sz(H)-1],p) >= 0) H.pop_back();
		H.push_back(p);
	}
	for(auto p : H) CH.insert(p);
	return H[1];
}



int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	scanf("%d",&n);
	loop(i,n) scanf("%d %d",&I[i].first,&I[i].second);
	auto ptr = min_element(I,I + n);
	rotate(I,ptr,I + n);
	vector<pi> P{I,I + n};
	sort(all(P));
	pi target = getHull(P);
	reverse(all(P));
	getHull(P);
	for(int i = 1;i < n;i++) {
		if(CH.count(I[i])) {
			puts((target == I[i]) ? "cw" : "ccw");
			return 0;
		}
	}
	return 0;
}
#endif
