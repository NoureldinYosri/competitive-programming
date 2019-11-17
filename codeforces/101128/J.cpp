#ifdef ACTIVE
#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define all(A) A.begin(),A.end()
#define pb push_back
#define mp make_pair
#define sz(A) ((int)A.size())
typedef std::vector<int> vi;
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

typedef std::pair<ll,ll> pi;

pi P[1 << 20],O;
int n;

pi operator - (const pi & a,const pi & b) {
	return pi(a.first - b.first,a.second - b.second);
}

ll cross(pi a,pi b) {
	return a.first*(ll)b.second - a.second*(ll)b.first;
}

ll cross(pi o,pi a,pi b) {
	return cross(a-o,b-o);
}

vector<pi> getSide() {
	vector<pi> side;
	for(int i = 0;i < n;i++) {
		pi p = P[i];
		while(sz(side) > 1 && cross(side[sz(side)-2],side[sz(side)-1],p) >= 0) side.pop_back();
		side.push_back(p);
	}
	return side;
}


auto cmp = [](const pi & a,const pi & b) {
	return cross(a,b) > 0;
};

vector<pi> getHull(){
	sort(P,P + n);
	auto up = getSide();
	reverse(P,P + n);
	auto down = getSide();

	up.pop_back();
	down.pop_back();
	vector<pi> hull;
	for(auto p : up) hull.push_back(p);
	for(auto p : down) hull.push_back(p);

	vector<pi> aux;
	for(auto p : hull) aux.emplace_back(p.second,p.first);
	sort(all(aux));
	O = pi(aux[0].second,aux[0].first);

	aux.clear();
	for(pi & p : hull) {
		p = p - O;
		if(p != pi(0,0))
			aux.push_back(p);
		assert(!(p.first < 0 && p.second == 0));
		assert(p.second >= 0);
	}

	sort(all(aux),cmp);
	hull.clear();
//	hull.push_back(pi(0,0));
	for(auto p : aux)
		hull.push_back(p);


	return hull;
}

int sgn(ll x) {
	return (x > 0) - (x < 0);
}

bool inRange(int l,int r,int x) {
	if(l > r) swap(l,r);
	return l <= x && x <= r;
}

bool inSegment(pi a,pi b,pi p) {
	if(a > b) swap(a,b);
	if(cross(a,b,p)) return 0;
	return inRange(a.first,b.first,p.first)
			&& inRange(a.second,b.second,p.second);
}

bool inTri(pi a,pi b,pi c,pi p) {
//	cout << p << endl;
	if(inSegment(a,b,p)) return 1;
	if(inSegment(b,c,p)) return 1;
	if(inSegment(c,a,p)) return 1;

	int s1 = sgn(cross(p,a,b));
	int s2 = sgn(cross(p,b,c));
	int s3 = sgn(cross(p,c,a));

	if(!s1 || !s2 || !s3) return 0;
	return s1 == s2 && s2 == s3;
}

bool inHull(pi p,vector<pi> & hull) {
//	cout << "testing " << p << endl;
	if(p.second < 0) return 0;
	if(cross(p,hull[0]) > 0) return 0;
	if(cross(hull.back(),p) > 0) return 0;

	auto ptr = lower_bound(all(hull),p,cmp);
	int i = ptr - hull.begin();
	for(int j = -2;j <= 2;j++) {
		int k = i + j;
		if(k < 0) continue;
		if(k+1 >= sz(hull)) continue;
		if(inTri(pi(0,0),hull[k],hull[k+1],p))
			return 1;
	}

	return 0;
}

int main(){
#ifdef HOME
	freopen("in.in","r",stdin);
#endif
	scanf("%d",&n);
	loop(i,n) scanf("%lld %lld",&P[i].first,&P[i].second);

	auto hull = getHull();

	//	cout << O << endl;
//	for(auto p : hull)
//		cout  << "Segment " << p.first << " " << p.second << endl;

	int m; scanf("%d",&m);
	int ans = 0;
	loop(i,m){
		pi p; scanf("%lld %lld",&p.first,&p.second);
		p = p - O;
//		cout << p.first << " " << p.second << endl;
		ans += inHull(p,hull);
	}
	cout << ans << endl;
	return 0;
}

#endif
