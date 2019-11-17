#ifdef ACTIVE
#include <bits/stdc++.h>
using namespace std;

#define sz(A) (int)(A.size())
using pi = pair<int,int>;
using point = complex<double>;
int n;
point P[60],Q;
pi I[60];
const double PI = acos(-1);

pi readPoint() {
	int x,y; scanf("%d %d",&x,&y);
	return pi(x,y);
}

double cross(point o,point a,point b) {
	a -= o;
	b -= o;
	return (conj(a)*b).imag();
}
int cross(pi o,pi a,pi b) {
	a.first -= o.first,a.second -= o.second;
	b.first -= o.first,b.second -= o.second;
	return a.first*b.second - a.second*b.first;
}

double dot(point a,point b) {
	return (conj(a)*b).real();
}

double norm(point a,point b) {
	point d = a - b;
	return sqrt(dot(d,d));
}

void fix(){
	static vector<pi> aux;
	int c = 0;
	for(int i = 1;i < n;i++)
		if(I[i].second == 0 && I[i].first < I[c].first)
			c = i;
	rotate(I,I + c,I + n);
	aux.clear();
	for(int i = 0;i < n;i++){
		while(sz(aux) > 1 && cross(aux[sz(aux)-2],aux[sz(aux)-1],I[i]) <= 0)
				aux.pop_back();
		aux.push_back(I[i]);
	}
	n = 0;
	for(auto p : aux)
		P[n++] = point(p.first,p.second);
}

double R[3][3];

void rotateMatrix(double t,point p) {
	static double aux[3][3],res[3][3];
	double c = cos(-t),s = sin(-t);
	aux[0][0] = c;
	aux[0][1] = -s;
	aux[0][2] = -c*p.real() + s*p.imag() + p.real();
	aux[1][0] = s;
	aux[1][1] = c;
	aux[1][2] = -s*p.real() - c*p.imag() + p.imag();
	aux[2][0] = aux[2][1] = 0;
	aux[2][2] = 1;
//	for(int i = 0;i < 3;i++,cout << endl)
//		for(int j = 0;j < 3;j++)
//			cout << R[i][j] << " ";
//	for(int i = 0;i < 3;i++,cout << endl)
//		for(int j = 0;j < 3;j++)
//			cout << aux[i][j] << " ";
//
	for(int i = 0;i < 3;i++)
		for(int j = 0;j < 3;j++) {
			res[i][j] = 0;
			for(int k = 0;k < 3;k++)
				res[i][j] += aux[i][k]*R[k][j];
		}
	for(int i = 0;i < 3;i++){
		for(int j = 0;j < 3;j++){
			R[i][j] = res[i][j];
//			cout << R[i][j] << " ";
		}
//		cout << endl;
	}
}

point rotatePoint(point p) {
	double x = R[0][0]*p.real() + R[0][1]*p.imag() + R[0][2];
	double y = R[1][0]*p.real() + R[1][1]*p.imag() + R[1][2];
	return point(x,y);
}


double D[1 << 20];

int main(){
#ifdef HOME
	freopen("in.in","r",stdin);
#endif
	int T; scanf("%d",&T);
	for(int cn = 1;cn <= T;cn++) {
		scanf("%d",&n);
		for(int i = 0;i < n;i++) I[i] = readPoint();
		pi q = readPoint();
		Q = point(q.first,q.second);
//		fix();
		for(int i = 0;i < n;i++)
			P[i] = point(I[i].first,I[i].second);
		P[n] = P[0];
		P[n+1] = P[1];
		for(int i = 0;i <= n;i++)
			D[i] = norm(Q,P[i]);

		for(int i = 0;i < 3;i++)
			for(int j = 0;j < 3;j++)
				R[i][j] = i == j;
		double ans = 0;
		for(int i = 1;i <= n;i++) {
			double ct = dot(P[i-1]-P[i],P[i+1]-P[i]);
//			cout << P[i-1]-P[i] << " " << P[i+1] - P[i] << ": " << dot(P[i-1]-P[i],P[i+1]-P[i]) << endl;
			ct /= norm(P[i-1],P[i])*norm(P[i],P[i+1]);
//			cout << ct << endl;
			ct = max(ct,-1.0);
			ct = min(ct,1.0);
			double t = PI - acos(ct);
			point pivot = rotatePoint(P[i]);
//			cout << P[i] << " became " << pivot << " rotate by " << t << endl;
			double r = norm(pivot,Q);
			ans += r*t;
			rotateMatrix(t,pivot);
			Q = (Q - pivot)*polar(1.0,-t) + pivot;
//			cout << "to " << Q << endl;
		}
		printf("Case #%d: %.3f\n",cn,ans);
	}
	return 0;
}
#endif
