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


pi operator + (const pi & a,const pi & b) {
	return pi(a.first + b.first,a.second + b.second);
}
pi operator - (const pi & a,const pi & b) {
	return pi(a.first - b.first,a.second - b.second);
}

pi operator * (const int & c,const pi & v) {
	return pi(v.first*c,v.second*c);
}

int sgn(ll x) {
	return (x > 0) - (x < 0);
}


ll cross(pi o,pi a,pi b) {
	a.first -= o.first, a.second -= o.second;
	b.first -= o.first, b.second -= o.second;
	return a.first*(ll)b.second - a.second*(ll)b.first;
}

auto cmp = [](const pi & a,const pi & b) {
	if(a.second == 0) return a.first > 0;
	if(b.second == 0) return a.second > 0 && b.first < 0;
	if(sgn(a.second) == sgn(b.second)) return cross(pi(0,0),a,b) > 0;
	return a.second > 0;
};

double mag(pi p,bool takeRoot) {
	double L = p.first*(ll)p.first + p.second*(ll)p.second;
	if(takeRoot) L = sqrt(L);
	return L;
}

struct Jaw{
	pi cur,nxt,dir;
	Jaw(){}
	Jaw(pi p,pi q,pi r) {
		cur = p;
		nxt = q;
		dir = r;
	}
	double getCos(){
		pi p = dir;
		pi q = nxt - cur;
		pi t = q - p;
		return (mag(p,0) + mag(q,0) - mag(t,0))/(2*mag(p,1)*mag(q,1));
	}
	pi getDir() {
		return nxt - cur - dir;
	}
	bool rotate(pi dr) {
		dir = dir + dr;
		pi t = cur + dir;
		return cross(cur,nxt,t) == 0;
	}
	void set(pi q){
		cur = nxt;
		nxt = q;
	}
	friend ostream& operator << (ostream & st,const Jaw & J) {
		st << "{" << J.cur << ", " << J.dir << "}";
		return st;
	}
};

double PointLineDist(pi p,pi r,pi q) {
	double ans = abs(cross(p,q,p + r));
	ans /= hypot(r.first,r.second);
	return ans;
}

pi P[1 << 20];
int n;

void getOneSide(vp & U) {
	for(int i = 0;i < n;i++) {
		pi p = P[i];
		while(sz(U) > 1 && cross(U[sz(U)-2],U[sz(U)-1],p) >= 0) U.pop_back();
		U.push_back(p);
	}
}

void getConvexHull() {
	vp U,D;
	sort(P,P + n);
	getOneSide(U);
	reverse(P,P + n);
	getOneSide(D);
	reverse(all(U));
	reverse(all(D));
	U.pop_back();
	D.pop_back();
	n = 0;
	for(pi p : U) P[n++] = p;
	for(pi p : D) P[n++] = p;
//	for(int i = 0;i < n;i++)
//		cout << P[i] << " ";
//	cout << endl;
}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	int R; scanf("%d %d",&n,&R);
	int mx = INT_MIN,mn = INT_MAX;
	loop(i,n) {
		scanf("%d %d",&P[i].first,&P[i].second);
		mx = max(mx,P[i].first);
		mn = min(mn,P[i].first);
	}
	getConvexHull();
	int i = 0,j = 0;
	loop(k,n) {
		if(P[k].first == mx) i = k;
		if(P[k].first == mn) j = k;
	}
	Jaw A(P[i],P[(i+1)%n],pi(0,1)),B(P[j],P[(j+1)%n],pi(0,-1));
//	cerr << A << " " << B << endl;
	double ans = PointLineDist(A.cur,A.dir,B.cur);
	for(int k = 0;k < n;k++) {
		double c1 = A.getCos(),c2 = B.getCos();
		pi d1 = A.getDir(),d2 = B.getDir();
//		cerr << d1 << " " << d2 << " " << c1 << " " << c2 << ": " ;
		if(c1 >= c2) d2 = -1*d1;
		else d1 = -1*d2;
//		cerr << d1 << " " << d2 << endl;

		if(A.rotate(d1)) {
			i = (i + 1)%n;
			A.set(P[(i + 1)%n]);
		}
		if(B.rotate(d2)){
			j = (j + 1)%n;
			B.set(P[(j+1)%n]);
		}
//		cerr << A << " " << B << endl;
		ans = min(ans,PointLineDist(A.cur,A.dir,B.cur));
	}
	printf("%.10f\n",ans);
	return 0;
}
