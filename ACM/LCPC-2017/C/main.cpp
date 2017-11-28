#include <bits/stdc++.h>
#define ll long long
#define mp make_pair
#define vi vector<int>
#define pb push_back
#define loop(i,n) for(int i = 0;i < (n);i++)
#define LSOne(x) ((x) & (-(x)))
#define pi pair<int,int>
#define xx first
#define yy second
#define sz(A) (int((A).size()))
using namespace std;

const int MAX = 100*1000 + 10;
int n,m;
pi A[MAX],B[MAX];
deque<pi> CH1,CH2;


ll mycross(pi o,pi u,pi v) {
	u.xx -= o.xx,u.yy -= o.yy;
	v.xx -= o.xx,v.yy -= o.yy;
	return u.xx*1LL*v.yy - u.yy *1LL*v.xx;
}


void get_CH(pi *A,int n,deque<pi> & CH){
	sort(A,A + n);
	CH.clear();
	int k = 0;
	loop(i,n) {
		while(k > 1 && mycross(CH[k - 2],CH[k - 1],A[i]) >= 0) {
			k--;
			CH.pop_back();
		}
		k++;
		CH.push_back(A[i]);
	}
	for(int i = n-1;i >= 0;i--) {
		while(k > 1 && mycross(CH[k - 2],CH[k - 1],A[i]) >= 0) {
			k--;
			CH.pop_back();
		}
		k++;
		CH.push_back(A[i]);
	}
	reverse(CH.begin(),CH.end());
}


int sgn(ll v) {
	return (v > 0) - (v < 0);
}

bool inter(pi a,pi b,pi u,pi v) {
	if(mycross(a,b,u) == 0) return 1;
	if(mycross(a,b,v) == 0) return 1;
	if(mycross(u,v,a) == 0) return 1;
	if(mycross(u,v,b) == 0) return 1;
	return (sgn(mycross(a,b,u)) != sgn(mycross(a,b,v))) && (sgn(mycross(u,v,a)) != sgn(mycross(u,v,b)));
}



bool preprocess(){
	if(n < m ){
		loop(i,m) swap(A[i],B[i]);
		swap(n,m);
	}
	if(n == 2) {
		assert(m == 2);
		puts(inter(A[0],A[1],B[0],B[1]) ? "NO" : "YES");
		return 1;
	}
	get_CH(A,n,CH1);
	get_CH(B,m,CH2);
	return 0;
}


typedef complex<double> point;
#define EPS 1e-9
#define OO 1e9
#define	X real()
#define	Y imag()
#define all(A) (A).begin(),(A).end()
#define	vec(a,b) ((b)-(a))
#define	polar(r,t) ((r)*exp(point(0,(t))))
#define	angle(v) (atan2((v).Y,(v).X))
#define	length(v) ((long double)hypot((v).Y,(v).X))
#define	lengthSqr(v) (dot(v,v))
#define	dot(a,b) ((conj(a)*(b)).real())
#define	cross(a,b) ((conj(a)*(b)).imag())
#define	rotate(v,t) (polar(v,t))
#define	rotateabout(v,t,a) (rotate(vec(a,v),t)+(a))
#define	reflect(p,m) ((conj((p)/(m)))*(m))
#define	normalize(p) ((p)/length(p))
#define	same(a,b) (lengthSqr(vec(a,b))<EPS)
#define	mid(a,b) (((a)+(b))/point(2,0))
#define	perp(a) (point(-(a).Y,(a).X))
#define	colliner pointOnLine

enum STATE {
IN, OUT, BOUNDRY
};
bool intersect(const point &a, const point &b, const point &p,const point &q, point &ret) {
	//handle degenerate cases
	double d1 = cross(p - a, b - a);
	double d2 = cross(q - a, b - a);
	ret = (d1*q - d2*p)/(d1 - d2);
	return abs(d1 - d2) > EPS;
}

void polygonCut(const vector<point>& p, const point&a, const point&b, vector<point>& res) {
	res.clear();
	for (int i = 0; i < sz(p); i++) {
		int j = (i + 1) % sz(p);
		bool in1 = cross(vec(a,b),vec(a,p[i])) > EPS;
		bool in2 = cross(vec(a,b),vec(a,p[j])) > EPS;
		if (in1)
			res.push_back(p[i]);
		if (in1 ^ in2) {
			point r;
			intersect(a, b, p[i], p[j], r);
			res.push_back(r);
		}
	}
}

void convexPolygonIntersect(const vector<point>& p, const vector<point>& q, vector<point>& res) {
	res = p;
	for (int i = 0; i < sz(p); i++) {
		int j = (i + 1) % sz(p);
		vector<point> temp;
		polygonCut(res, p[i], p[j], temp);
		res = temp;
		if (res.empty())
			return;
	}
}

bool solve(){
	vector<point> P,Q,res;
	P.reserve(CH1.size());
	Q.reserve(CH2.size());
	for(auto p : CH1) P.pb(point(p.xx,p.yy));
	for(auto p : CH2) Q.pb(point(p.xx,p.yy));
	convexPolygonIntersect(P,Q,res);
	return res.empty();
}

int main(){
	freopen("milano.in","r",stdin);
	int T;
	scanf("%d",&T);
	for(int t = 1;t <= T;t++){
		scanf("%d %d",&n,&m);
		loop(i,n) scanf("%d %d",&A[i].xx,&A[i].yy);
		loop(i,m) scanf("%d %d",&B[i].xx,&B[i].yy);
		if(n == 1 && m <= 2) puts("YES");
		else if(n <= 2 && m == 1) puts("YES");
		else {
			if(preprocess()) continue;
			puts(solve() ? "YES" : "NO");
		}
	}

}
