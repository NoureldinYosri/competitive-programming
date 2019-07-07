#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define range(i,a,b) for(int i = (a);i <= (b);i++)
#define all(A) A.begin(),A.end()
#define pb push_back
#define mp make_pair
#define sz(A) ((int)A.size())
#define vi vector<int>
#define vl vector<long long>
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
const double PI = acos(-1);
using namespace std;


const double EPS = 1e-15;
struct point3d{
	double x,y,z;
	friend ostream& operator << (ostream & st,const point3d & p) {
		st << setprecision(3) << fixed << "(" << p.x << ", " << p.y << ", " << p.z << ")";
		return st;
	}
};

struct point2d{
	double x,y;
	friend ostream& operator << (ostream & st,const point2d & p) {
		st << setprecision(3) << fixed << "(" << p.x << ", " << p.y << ")";
		return st;
	}
	bool operator < (const point2d & o) const {
		return tie(x,y) < tie(o.x,o.y);
	}
};

point3d mat_point_mul(double R[3][3],point3d p) {
	point3d q;
	int r = 0;
	q.x = R[r][0] * p.x + R[r][1] * p.y + R[r][2] * p.z;
	r++;
	q.y = R[r][0] * p.x + R[r][1] * p.y + R[r][2] * p.z;
	r++;
	q.z = R[r][0] * p.x + R[r][1] * p.y + R[r][2] * p.z;
	return q;
}

void mat_mat_mul(double A[3][3],double B[3][3],double C[3][3]) {
	double D[3][3] = {0};
	loop(i,3) loop(j,3) loop(k,3) D[i][j] += A[i][k] * B[k][j];
	loop(i,3) loop(j,3) C[i][j] = D[i][j];
}

point3d P[8];
point3d centers[3];

void init(){
	auto sgn = [](const int & v){
		return (v > 0) ? -1 : 1;
	};
	loop(i,8) {
		P[i].x = 0.5*sgn(i&1);
		P[i].y = 0.5*sgn(i&2);
		P[i].z = 0.5*sgn(i&4);
	}
	centers[0] = {0.5,0,0};
	centers[1] = {0,0.5,0};
	centers[2] = {0,0,0.5};
}

double cross(point2d o,point2d p,point2d q) {
	double x1 = p.x - o.x,y1 = p.y - o.y;
	double x2 = q.x - o.x,y2 = q.y - o.y;
	return x1*y2 - x2*y1;
}

bool gZ(double x) {
	return x > 0 || abs(x) < EPS;
}

vector<point2d> pass(vector<point2d> & V) {
	vector<point2d> H;
	for(auto & p : V){
		while(sz(H) > 1 && gZ(cross(H[sz(H)-2],H[sz(H)-1],p)))
			H.pop_back();
		H.push_back(p);
	}
	return H;
}

double get_area(point3d *Q) {
	vector<point2d> V;
	loop(i,8) V.push_back(point2d({Q[i].x,Q[i].z}));
	sort(all(V));
	auto H = pass(V);
	reverse(all(V));
	auto D = pass(V);
	double h = 0,d = 0;
	for(int i = 1;i + 1 < sz(H);i++)
		h += cross(H[0],H[i],H[i + 1]);
	h = abs(h)/2;
	for(int i = 1;i + 1 < sz(D);i++)
		d += cross(D[0],D[i],D[i + 1]);
	d = abs(d)/2;
//	print(H,point2d);
//	print(D,point2d);
	return h + d;
}


void make_eye(double R[3][3]) {
	loop(i,3)loop(j,3) R[i][j] = i==j;
}
void make_x(double R[3][3],double t) {
	double c = cos(t),s = sin(t);
	loop(i,3) loop(j,3) R[i][j] = 0;
	R[0][0] = 1;
	R[1][1] = c;
	R[1][2] = -s;
	R[2][1] = s;
	R[2][2] = c;
}
void make_y(double R[3][3],double t) {
	double c = cos(t),s = sin(t);
	loop(i,3) loop(j,3) R[i][j] = 0;
	R[0][0] = c;
	R[0][2] = s;
	R[2][0] = -s;
	R[2][2] = c;
	R[1][1] = 1;
}
void make_z(double R[3][3],double t) {
	double c = cos(t),s = sin(t);
	loop(i,3) loop(j,3) R[i][j] = 0;
	R[0][0] = c;
	R[0][1] = -s;
	R[1][0] = s;
	R[1][1] = c;
	R[2][2] = 1;
}


void apply(double x,double y,double z,point3d Q[8]) {
	double X[3][3],Y[3][3],Z[3][3];
	make_x(X,x);
	make_y(Y,y);
	make_z(Z,z);
	mat_mat_mul(Y,Z,Y);
	mat_mat_mul(X,Y,X);
	loop(i,8)
		Q[i] = mat_point_mul(X,P[i]);
}


double get_rot_area(double x,double y,double z) {
	point3d Q[8];
	apply(x,y,z,Q);
	return get_area(Q);
}

double TSZ(double x,double y,double & z) {
	double s = 0,e = PI/4;

	for(int i = 0;i < 30 && s < e;i++) {
		double m1 = s + (e-s)/3;
		double m2 = m1 + (e-s)/3;
		if(get_rot_area(x,y,m1) > get_rot_area(x,y,m2)) e = m2;
		else s = m1;
	}
	z = s;
	double a = get_rot_area(x,y,s),b = get_rot_area(x,y,e);
	double ret = a;
	if(b > a){
		z = e;
		ret = b;
	}
	return ret;
}

double BSZ(double t,double x,double y,double e) {
	double s = 0;

	for(int i = 0;i < 30 && s < e;i++) {
		double m = s + (e-s)/2;
		if(get_rot_area(x,y,m) >= t) e = m;
		else s = m;
	}
	return s;
}

const int N = 30;
struct cand{
	double x,y,e,mn,mx;
};
vector<cand> C;


void init_DS(){
	double T = PI/4;
	for(int i = 0;i < N;i++)
		for(int j = 0;j < N;j++) {
			double x = i*T/(N-1);
			double y = j*T/(N-1);
			double z;
			double mx = TSZ(x,y,z);
//			cerr << setprecision(6) << fixed << " " << x << " " << y << " min = " << get_rot_area(x,y,0) << " mx = " << mx << endl;
			cand c;
			c.x = x;
			c.y = y;
			c.e = z;
			c.mn = get_rot_area(x,y,0);
			c.mx = mx;
			C.push_back(c);
		}
}

bool leq(double x,double y) {
	return x < y || abs(x-y) < EPS;
}

void solve(double t,double & x,double & y,double & z) {
	bool found = 0;
	for(cand & c : C) if(leq(c.mn ,t) && leq(t, c.mx) ) {
		x = c.x;
		y = c.y;
		z = c.e;
		found = 1;
		break;
	}
	assert(found);
	z = BSZ(t,x,y,z);
#ifdef HOME
//		cerr << setprecision(6) << fixed << t << " vs " << get_rot_area(x,y,z) << endl;
#endif
}


int main(){
	#ifdef HOME
		freopen("in.in", "r", stdin);
//		freopen("err.log","w",stderr);
	#endif
	init();
	init_DS();
	double x,y,z;

	int T; scanf("%d",&T);
	for(int t = 1;t <= T;t++) {
		double target;
		scanf("%lf",&target);
		solve(target,x,y,z);
		double X[3][3],Y[3][3],Z[3][3];
		make_x(X,x);
		make_y(Y,y);
		make_z(Z,z);
		mat_mat_mul(Y,Z,Y);
		mat_mat_mul(X,Y,X);

		printf("Case #%d:\n",t);
		loop(i,3){
			auto p = mat_point_mul(X,centers[i]);
			printf("%.6f %.6f %.6f\n",p.x,p.y,p.z);
		}
	}



	return 0;
}
