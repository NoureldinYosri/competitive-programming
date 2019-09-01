#ifndef GEO
#define GEO
#include <bits/stdc++.h>
using namespace std;
const double EPS = 1e-12;
using point = std::complex<double>;
#define dot(p,q) ((p)*conj(q)).real()
#define norm(p) dot((p),(p))
#define mag(p) sqrt(norm(p))
#define cross(p,q) (conj(p)*(q)).imag()

bool same(double a,double b) {
	return abs(a-b) < EPS;
}
bool leq(double a,double b) {
	return a < b || same(a,b);
}
double pointLineDist(point p,point a,point b) {
	assert(!same(norm(a-b),0));
	return abs(cross(p-a,b-a))/mag(a-b);
}

double pointSegmentDist(point p,point a,point b) {
	if(same(norm(a-b),0)) return mag(p-a);
	double d = pointLineDist(p,a,b);
	double x = dot(p-a,b-a),y = dot(p-b,a-b);
	return (leq(0,x) && leq(0,y)) ? d : min(mag(p-a),mag(p-b));
}
bool pointInPoly(point p,point *P,int n){
	//assumes convex polygon in ccw order
	loop(i,n){
		int j = (i + 1)%n;
		double s = cross(P[i]-p,P[j]-p);
//		cout << p << " " << P[i] << " " << P[j] << " " << s << endl;
		if(!leq(0,s)) return 0;
	}
	return 1;
}
std::istream& operator >> (std::istream & is,point & p) {
	double x,y;
	is >> x >> y;
	p = point(x,y);
	return is;
}

#endif
