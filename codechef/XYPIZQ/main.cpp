#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define range(i,a,b) for(int i = (a);i <= (b);i++)
#define all(A) A.begin(),A.end()
#define pb push_back
#define mp make_pair
#define sz(A) ((int)A.size())
#define vi vector<int>
#define vd vector<double>
#define vp vector<pair<int,int> >
#define ll long long
#define popcnt(x) __builtin_popcountll(x)
#define LSOne(x) ((x) & (-(x)))
#define xx first
#define yy second
#define PQ priority_queue
#define print(A,t) cerr << #A << ": "; copy(all(A),ostream_iterator<t>(cerr," " )); cerr << endl
#define prp(p) cerr << "(" << (p).first << " ," << (p).second << ")";
#define prArr(A,n,t)  cerr << #A << ": "; copy(A,A + n,ostream_iterator<t>(cerr," " )); cerr << endl
#define PRESTDIO() cin.tie(0),cerr.tie(0),ios_base::sync_with_stdio(0)
#define what_is(x) cerr << #x << " is " << x << endl
#define bit_lg(x) (assert(x > 0),__builtin_ffsll(x) - 1)
using namespace std;

const double PI = acos(-1);
typedef complex<double> point;
typedef pair<ll,ll> pl;
vector<point> A,B;


inline double len(point p) {
	return sqrt((p*conj(p)).real());
}

point getA(point b,double x,double alpha) {
	double sPhi = sin(alpha) * len(b)/x;
	double phi = asin(sPhi);
	double t = PI - phi - alpha;
	double len2 = len(b)*len(b) + x*x - 2*len(b)*x*cos(t);
	double len = sqrt(len2);
	return polar(len,0.0);
}

point getB(point a,double x,double alpha) {
	double s = sin(alpha) * len(a)/x;
	double phi = asin(s);
	double theta = phi + alpha;
	return a + polar(x,theta);
}

void build(int n){
	double alpha = PI/(2*n + 1);
	double x = 1;
	A.push_back(polar(0.0,0.0));
	A.push_back(polar(1.0,0.0));
	B.push_back(polar(0.0,0.0));
	B.push_back(polar(1.0,alpha));
	for(int i = 2;i <= n;i++) {
		point a = A.back(),b = B.back();
		// x/sin(alpha) = |da|/sin(phi)
		A.push_back(getA(b,x,alpha));
		B.push_back(getB(a,x,alpha));
	}
	point a = getA(B.back(),x,alpha) - A.back();
	point b = getB(A.back(),x,alpha) - B.back();
//	cerr << a << " " << b << endl;
	assert(len(a) < 1e-9);
	assert(len(b) < 1e-9);
}

double arg(point p) {
	double t = atan2(p.imag(),p.real());
	if(abs(t) < 1e-12) t = 0;
	if(t < 0) t += 2*PI;
	return t;
}

ll Gcd(ll a,ll b) {
	while(b) {
		ll t = a%b;
		a = b;
		b = t;
	}
	return a;
}

ll Lcm(ll a,ll b) {
	return a*(b/Gcd(a,b));
}

pl operator + (const pl & a,const pl & b) {
	ll m = Lcm(a.yy,b.yy);
	ll n = a.xx*(m/a.yy) + b.xx * (m/b.yy);
	ll g = Gcd(m,n);
	m /= g,n /= g;
	return mp(n,m);
}

pl operator * (const ll & c,const pl & p) {
	ll x = c*p.xx,y = p.yy;
	ll g = Gcd(x,y);
	x /= g,y /= g;
	return mp(x,y);
}

ostream& operator << (ostream & st,const pl & p) {
	st << p.xx << "/" << p.yy;
	return st;
}

int sgn(int x) {
	return (x > 0) - (x < 0);
}

bool valid(int x,int y,int z) {
	int s = sgn(y-x) + sgn(z-y);
	return s == -2 || s == 0 || s==2;
}



pl t1(int x,int y,int z,ll n) {
	if(x == z) return mp(x,2*n+1);
	//aab
	if(y == x+1 && z == y+1) return pl(2*n-1-x,2*n+1);
	return pl(2*n+1-z,2*n + 1) ;
}

pl t2(int x,int y,int z,ll n) {
	//aba
	if(x == z) return mp(0,1);
	if(y==x-1 && z==y-1) return mp(2*n-1-2*z,2*n+1);
	return t2(z,y,x,n);
}

pl t3(int x,int y,int z,ll n) {
	//abb
	if(x == z) {
		if(x < y)
			return mp(x,2*n+1);
		else
			return mp(4*n+1-y,2*n+1);
	}
	if(x < y) return mp(2*n + 1 + x,2*n + 1);
	return mp(2*n-1-z,2*n+1);
}

pl t4(int x,int y,int z,ll n) {
	//bab
	if(x == z) return mp(0,1);
	if(x > z) return t4(z,y,x,n);
	return mp(2*n-1-2*x,2*n+1);
}

pl solve(int n,int t,int x,int y,int z){
	A.clear(),B.clear();
	build(n);
	vector<point>* X[] = {0,&A,&A,&A,&B};
	vector<point>* Y[] = {0,&A,&B,&B,&A};
	vector<point>* Z[] = {0,&B,&A,&B,&B};
	point a = (*X[t])[x];
	point b = (*Y[t])[y];
	point c = (*Z[t])[z];
	a -= b,c -= b;
	double alpha = PI/(2*n + 1);
	ll u = round(abs(arg(a) - arg(c)) / alpha);
	ll v = 2*n + 1;
	if(u > v) u = 2*v - u;
	ll g = Gcd(u,v);
	u /= g,v /= g;
	return pl(u,v);
}

pl getAnswer(int n,int t,int x,int y,int z){
	pl ans;
	if(t==1) ans = t1(x,y,z,n);
	else if(t==2) ans = t2(x,y,z,n);
	else if(t==3) ans = t3(x,y,z,n);
	else ans = t4(x,y,z,n);
	if(ans.xx > ans.yy) ans.xx = 2*ans.yy - ans.xx;
	ll g = Gcd(ans.xx,ans.yy);
	ans.xx /= g;
	ans.yy /= g;
	return ans;
}

int getCand(int x,int n) {
	vi cand;
	if(x) cand.pb(x-1);
	if(x < n) cand.pb(x+1);
	if(cand.empty()) return -1;
	return cand[rand()%sz(cand)];
}

void test(){
	string S[] = {"","aab","aba","abb","bab"};
	for(int cs = 1;cs <= 10000;cs++) {
		int n = rand()%50 + 1;
		int t = rand()%4 + 1;
		int x = rand()%(n + 1);
		int y = getCand(x,n);
		int z = getCand(y,n);
		string s = S[t];
		int V[] = {x,y,z};
		bool c = 1;
		loop(i,3) if((s[i] == 'b' && V[i] == 0) || V[i] < 0) c = 0;
		if(!c) {
			cs--;
			continue;
		}
		pl u = getAnswer(n,t,x,y,z), v = solve(n,t,x,y,z);
		if(u != v){
			cerr << "fail on case " << n << " " << t << " " << x << " " << y << " " << z << endl;
			cerr << "expected " << v << " found " << u << endl;
			exit(0);
		}
	}
	cout << "success :)" << endl;
}

int main(int argc,char **argv){
#ifdef HOME
	freopen("in.in","r",stdin);
#endif
	int T; scanf("%d",&T);
	while(T--) {
		int n,t,x,y,z;
		scanf("%d %d %d %d %d",&n,&t,&x,&y,&z);

		pl ans = getAnswer(n,t,x,y,z);
		printf("%lld %lld\n",ans.xx,ans.yy);
	}

//	test();
	return 0;
}
