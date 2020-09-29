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
const int MAX = 111;
int X[MAX],H[MAX],B[MAX];
int n;
pair<pi,pi> segments[MAX*2];
using point = complex<double>;


bool same(double x,double y) {
	return abs(x-y) < EPS;
}
bool leq(double x,double y) {
	return x < y || abs(x-y) < EPS;
}



double getY(pair<pi,pi> seg,double x) {
	double dx = seg.second.first - seg.first.first;
	double dy = seg.second.second - seg.first.second;
	x -= seg.first.first;
	return seg.first.second + x*dy/dx;
}

double cross(point a,point b) {
	return (conj(a)*b).imag();
}

point getIntersection(pi A,pi B,pi C,pi D) {
	point a (A.first,A.second);
	point b (B.first,B.second);
	point c (C.first,C.second);
	point d (D.first,D.second);
	b -= a,d -= c;
	d *= -1;
	double lambda = cross(c-a,d)/cross(b,d);
	return a + lambda * b;
}

double solve(){
	double ans = 0;
	loop(i,n) {
		segments[2*i] = mp(pi(X[i]-B[i]/2,0),pi(X[i],H[i]));
		segments[2*i+1] = mp(pi(X[i],H[i]),pi(X[i]+B[i]/2,0));
	}
	sort(segments,segments + 2*n);
	vector<pair<double,double>> events;
	loop(i,2*n) {
		events.clear();
		loop(j,2*n){
			if(i == j) continue;
			int l = max(segments[i].first.first,segments[j].first.first);
			int r = min(segments[i].second.first,segments[j].second.first);
			bool debug = i == 1 && j == 0;
			if(l >= r) continue;

			pair<double,double> f = mp(getY(segments[i],l),getY(segments[i],r));
			pair<double,double> g = mp(getY(segments[j],l),getY(segments[j],r));
			if(same(f.first,g.first) && same(f.second,g.second)) {
				if(i < j) continue;
				events.emplace_back(l,r);
				continue;
			}
//			if(debug) cout << f << " " << g << endl;
			if(leq(g.first,f.first) && leq(g.second,f.second)) continue;
			if(leq(f.first,g.first) && leq(f.second,g.second)) events.emplace_back(l,r);
			else {
				point p_cut = getIntersection(segments[i].first,segments[i].second,
						segments[j].first,segments[j].second);
//				cout << segments[i] << " " << segments[j] << " meet at " << p_cut << " ";
				double x_cut = p_cut.real();
//				cout << getY(segments[i],x_cut) << " " << getY(segments[j],x_cut) << endl;
				if(leq(f.first,g.first)) events.emplace_back(l,x_cut);
				else events.emplace_back(x_cut,r);
			}
//			if(debug) cout << segments[i] << " is covered by " << segments[j] << " in " << events.back() << endl;
		}
		sort(all(events));
//		cout << segments[i] << " has these covered: ";
		double s = 0,e = 0,badx = 0;
		bool f = 1;
		for(auto p : events) {
			if(!f && leq(p.first,e)) e = max(e,p.second);
			else {
//				if(!f) cout << point(s,e) << " ";
				f = 0;
				badx += e-s;
				s = p.first;
				e = p.second;
			}
		}
//		if(!f) cout << point(s,e);
//		cout << endl;
		badx += e-s;
		double dx = abs(segments[i].second.first-segments[i].first.first);
		double dy = abs(segments[i].second.second-segments[i].first.second);
		double bady = dy*badx/dx;
		double badLen = sqrt(badx*badx + bady*bady);

		double tmp = sqrt(dx*dx + dy*dy) - badLen;
//		cout << segments[i] << " " << tmp << endl;
		ans += tmp;
	}
	ans /= 2;
	return ans;
}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	for(int t = 1; scanf("%d",&n) == 1 && n;t++) {
		vector<pair<int,pi>> I;
		loop(i,n) {
			scanf("%d %d %d",X + i,H + i,B + i);
			X[i] <<= 1;
			H[i] <<= 1;
			B[i] <<= 1;
			I.emplace_back(X[i],mp(H[i],B[i]));
		}
		sort(all(I));
		I.resize(unique(all(I)) - I.begin());
		n = I.size();
		loop(i,n) {
			X[i] = I[i].first;
			H[i] = I[i].second.first;
			B[i] = I[i].second.second;
		}
//		loop(i,n){
//			cout << "Segment " << X[i] - B[i]/2 << " 0 " << X[i] << " " << H[i] << endl;
//			cout << "Segment " << X[i] << " " << H[i] << " " << X[i] + B[i]/2 << " 0" << endl;
//		}
		printf("Case %d: %.0f\n\n",t,solve());
	}
	return 0;
}
