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


struct point3d{
	ll P[3];
	point3d(){
		memset(this,0,sizeof *this);
	}
	point3d(ll x,ll y,ll z) {
		P[0] = x;
		P[1] = y;
		P[2] = z;
	}
	friend istream& operator >> (istream & st,point3d & p) {
		loop(i,3) st >> p.P[i];
		return st;
	}
	friend ostream& operator << (ostream & st,const point3d & p) {
		st << "(";
		loop(i,3) {
			st << p.P[i];
			if(i < 2) st << ", ";
		}
		st << ")";
		return st;
	}

	point3d operator - (const point3d & o) {
		point3d ret;
		loop(i,3) ret.P[i] = P[i] - o.P[i];
		return ret;
	}
	point3d cross(const point3d & o) {
		point3d ret;
		loop(i,3) {
			int sgn = (i%2 == 0) ? 1 : -1;
			ret.P[i] = 0;
			int j = (i == 0) ? 1 : 0;
			int k = 3 - i - j;
			ret.P[i] = sgn*(P[j]*o.P[k] - P[k]*o.P[j]);
		}
		return ret;
	}
	ll dot(const point3d & o) {
		ll ret = 0;
		loop(i,3) ret += P[i]*o.P[i];
		return ret;
	}
	bool isZero(){
		loop(i,3) if(P[i]) return 0;
		return 1;
	}
};

using point = pair<ll,ll>;

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	point3d A,B,C,D;
	cin >> A >> B >> C >> D;

	point3d n = (B - A).cross(D - A);
	if(n.isZero()){
		puts("Invalid");
		return 0;
	}
//	cout << n << endl;
	if(n.dot(C - A) == 0){
		point3d x = B - A;
		point3d y = n.cross(x);
//		cout << x << " " << y << endl;
		point b (x.dot(B-A),y.dot(B - A));
		point c (x.dot(C-A),y.dot(C - A));
		point d (x.dot(D-A),y.dot(D - A));
//		cout << b << " " << c << " " << d << endl;
		if(c.first == d.first && c.first >= b.first) {
			ll y1 = c.second,y2 = d.second;
			bool yes = 0;
			if(y1 == 0) yes = y2 != 0;
			else yes = (y1 > 0 && y2 > 0) || (y1 < 0 && y2 < 0);
			yes &= abs(y1) < abs(y2);
			puts(yes ? "Valid" : "Invalid");
		}
		else puts("Invalid");
	}
	else puts("Invalid");



	return 0;
}
#endif
