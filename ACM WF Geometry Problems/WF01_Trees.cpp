#ifdef ACTIVE
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
#define pi pair<int,int>
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

const double PI = acos(-1),EPS = 1e-15;
struct Tree{
	int x,y,d,h;
	friend ostream& operator << (ostream & st,const Tree & t) {
		st << "{(" << t.x << ", " << t.y << "), " << t.d << ", "
				<< t.h << "}";
		return st;
	}
};

int xmin,xmax,ymin,ymax,n;
Tree T[100];

bool read(){
	scanf("%d %d %d %d %d",&xmin,&ymin,&xmax,&ymax,&n);
	if(xmin==0 && ymin==0 && xmax==0 && ymax==0 && n==0) return 0;
	loop(i,n) scanf("%d %d %d %d",&T[i].x,&T[i].y,&T[i].d,&T[i].h);
	return 1;
}

void translate(){
	ymax -= ymin;
	xmax -= xmin;
	loop(i,n){
		T[i].x -= xmin;
		T[i].y -= ymin;
	}
	ymax *= 2;
	xmax *= 2;
	loop(i,n){
		T[i].x <<= 1;
		T[i].y <<= 1;
		T[i].d <<= 1;
		T[i].h <<= 1;
	}
}

typedef pair<double,double> pd;
deque<Tree> forest;
vector<pd> forbidden;

inline double make_2pi(double x){
	if(abs(x) < EPS) x = 0;
	if(x >= 0) return x;
	return x + 2*PI;
}

bool cos_law(double a,double b,double c,double & theta) {
	double ct = (a*a+b*b-c*c)/(2*a*b);
	if(abs(-1 - ct) < EPS) ct = -1;
	if(abs(1 - ct) < EPS) ct = 1;
	if(ct < -1 || ct > 1) return 0;
	theta = acos(ct);
	return 1;
}

bool leq(double a,double b) {
	return a <= b || abs(a-b) < EPS;
}

void insert(double s,double e) {
//	cerr << s*180/PI << " " << e*180/PI << endl;
	assert(leq(s,e));
	assert(leq(0,s));
	assert(leq(e,2*PI));
	forbidden.pb(mp(s,e));
}

void add_region(double s,double e) {
	if(leq(e,0)) {
		assert(leq(s,0));
		s += 2*PI;
		e += 2*PI;
		swap(s,e);
		insert(s,e);
		return;
	}
	if(leq(s,0)) {
		insert(2*PI+s,2*PI);
		insert(0,e);
		return;
	}
//	cerr << s << " " << e << endl;
//	cerr << "\t" << (s + e)/2 << " " << (e-s)/2 << endl;
	assert(leq(s,2*PI));
	if(leq(e,2*PI))
		insert(s,e);
	else{
		insert(s,2*PI);
		insert(0,e-2*PI);
	}
}

void get_forbidden(Tree a,Tree b) {
	ll d2 = (a.x - b.x)*(a.x - b.x + 0LL) + (a.y - b.y + 0LL)*(a.y - b.y);
	if((a.h + b.d/2L)*(a.h + b.d/2L) <= d2)
		return;
	ll r = (a.d + b.d) / 2;

	if(r*r > d2) return;
	double d = sqrt(d2);
	double theta = atan2(r,d);
//	cerr << "theta = " << theta << endl;
//	cerr << a.d << " " << b.d << "\t" << r << " " << d << endl;
	assert(leq(0,theta) && leq(theta,PI));
	double phi = atan2(b.y - a.y,b.x - a.x);
	phi = make_2pi(phi);
	add_region(phi - theta,phi + theta);
}

double get_union(){
	if(forbidden.empty()) return 0;
	for(auto p : forbidden){
		assert(leq(0,p.xx));
		assert(leq(p.xx,p.yy));
		assert(leq(p.yy,2*PI));
	}
	double ret = 0;
	sort(all(forbidden));
	double s = forbidden[0].xx,e = forbidden[0].yy;
	for(auto p : forbidden) {
		if(leq(p.xx,e)) e = max(e,p.yy);
		else {
			ret += e - s;
			s = p.xx;
			e = p.yy;
		}
	}
	ret += e - s;
	return ret;
}



int solve(){
	translate();
	forest.clear();
	loop(i,n) forest.push_back(T[i]);
	int ret = 0,done = 0;
	do{
		done = 1;
		int L = sz(forest);
		for(int i = 0;i < L;i++) {
			Tree ct = forest[i];
//			cerr << "processing " << ct.d << " " << endl;
			forbidden.clear();
			for(int j = 0;j < L;j++) {
				if(i != j) {
					get_forbidden(ct,forest[j]);
				}
			}
			double phi[] = {0,PI/2,PI,3*PI/2};
			int dist [] = {xmax - ct.x,ymax - ct.y,ct.x,ct.y};
			loop(i,4) {
				if(abs(dist[i]) >= ct.h) continue;
				ll r = ct.d/2;
				double l = sqrt(r*r + ct.h*(ll)ct.h);
				double d = abs(dist[i]);
				double theta = asin(r/l) + acos(d/l);
//				cerr << theta << ": " << r << " " << d << " " << l;
				assert(leq(0,theta));
				assert(leq(theta,PI));
				add_region(phi[i] - theta,phi[i] + theta);
			}
//			for(auto p : forbidden){
//				prp(p);
//			}
//			cerr << endl;
			double tot = get_union();
			bool can_be_cut = 1;
			if(leq(2*PI,tot))
				can_be_cut = 0;
			if(!can_be_cut)
				forest.push_back(ct);
			else
				ret++,done = 0;
		}
//		cerr << endl;
		loop(i,L) forest.pop_front();
//		print(forest,Tree);
	}while(!done);
	return ret;
}

int main(int argc,char **argv){
#ifdef HOME
	freopen("in.in","r",stdin);
#endif
	for(int t = 1;read();t++) {
		int ans = solve();
		printf("Forest %d\n",t);
		printf("%d tree(s) can be cut\n",ans);
		puts("");
	}
	return 0;
}
#endif
