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

const double EPS = 1e-12;
const int MAX = 100*1000 + 10;
using point = complex<double>;
pi I[MAX];
int n,K;

bool same(double x,double y) {
	return abs(x-y) < EPS;
}

bool leq(double x,double y) {
	return x < y || abs(x-y) < EPS;
}


void calc(point p,double r,vector<pair<double,int>> & events,bool rev) {
	double d2 = (p*conj(p)).real();
	double y = -d2/(2*r);
	double xr = sqrt(d2)/(2*r) * sqrt(max(0.0,4*r*r - d2)),xl = -xr;
	double theta = arg(p);
	double phi1 = atan2(y,xr);
	double phi2 = atan2(y,xl);
	double t1 = theta - phi1,t2 = theta-phi2;
	if(same(t1,0)) t1 = 0;
	if(same(t2,0)) t2 = 0;
	assert(leq(0,t1));
	assert(t1 <= t2);
	assert(leq(t2,2*PI));
	if(rev) {
		t1 += PI;
		t2 += PI;
		if(leq(2*PI,t1)) {
			t1 -= 2*PI;
			t2 -= 2*PI;
		}
		if(same(t1,0)) t1 = 0;
		if(same(t2,0)) t2 = 0;
		assert(t1 <= t2);
		events.emplace_back(t1,-1);
		if(leq(t2,2*PI)) events.emplace_back(t2,1);
		else {
			events.emplace_back(2*PI,1);
			events.emplace_back(0,-1);
			events.emplace_back(min(t1,t2-2*PI),1);
		}
	}
	else {
		events.emplace_back(t1,-1);
		events.emplace_back(t2,1);
	}
}



bool can(double r) {
	static vector<point> P[2];
	loop(i,2) P[i].clear();
	loop(i,n) {
		ll d2 = I[i].first*I[i].first+ I[i].second*I[i].second;
		if(leq(d2,4*r*r)) {
			int region = I[i].second < 0 || (I[i].second == 0 && I[i].first < 0);
			int sgn = 1-2*region;
			P[region].emplace_back(I[i].first*sgn,I[i].second*sgn);
		}
	}

//	print(P[0],point);
//	print(P[1],point);
	if(sz(P[0]) + sz(P[1]) < K) return 0;
	static vector<pair<double,int>> events;
	events.clear();
	for(auto p : P[0])
		calc(p,r,events,0);
	for(auto p : P[1])
		calc(p,r,events,1);

	sort(all(events));
//	for(auto e : events) cout << e << " ";
//	cout << endl;
	int k = 0,mx = 0;
	for(auto e : events) {
		k -= e.second;
		mx = max(mx,k);
	}
	return mx >= K;
}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	scanf("%d %d",&n,&K);
	loop(i,n) {
		int x,y; scanf("%d %d",&x,&y);
		I[i] = pi(x,y);
	}
	double s = 0,e = 1e9;
	for(int t = 0;s < e && t < 100;t++){
		double m = s + (e-s)/ 2.0;
		if(can(m)) e = m;
		else s = m;
	}
	if(!can(e)) puts("-1");
	else printf("%.10f\n",s);
	return 0;
}
