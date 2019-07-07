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

const double PI = acos(-1);
struct point3d{
	int coord[3];
	int x(){return coord[0];}
	int y(){return coord[1];}
	int z(){return coord[2];}
	double dist(const point3d & o){
		double dr = 0;
		loop(i,3) {
			double d = coord[i] - o.coord[i];
			dr += d*d;
		}
		return sqrt(dr);
	}
	friend istream& operator >> (istream & st,point3d & p) {
		loop(i,3) st >> p.coord[i];
		return st;
	}
	friend ostream& operator << (ostream & st,point3d & p) {
		st << "(";
		loop(i,3) {
			st << " ";
			if(i) st << ",";
			st << fixed << setprecision(3) << p.coord[i];
		}
		st << ")";
		return st;
	}
	point3d operator - (const point3d & o) {
		point3d ret;
		loop(i,3) ret.coord[i] = coord[i] - o.coord[i];
		return ret;
	}
};

struct circle{
	point3d center;
	double radius;
};

double solve(point3d *P,int n,point3d corner) {
	static vector<circle> C;
	C.clear();
	double area = 0;
	for(int i = 0;i < n;i++) {
		bool valid = 1;
		loop(j,3) valid &= P[i].coord[j] > 0 && P[i].coord[j] < corner.coord[j];
		for(const circle & c : C) {
			double d = P[i].dist(c.center);
			double r = c.radius;
			if(d < r) valid = 0;
		}
		if(!valid) continue;
		double r = 1e18;
		loop(j,3) {
			r = min(r,P[i].coord[j] + 0.0);
			r = min(r,corner.coord[j] - P[i].coord[j] + 0.0);
		}
		for(const circle & c : C) {
			double d = P[i].dist(c.center);
			r = min(r,d - c.radius);
		}
		area += r*r*r;
		circle c;
		c.center = P[i];
		c.radius = r;
		C.push_back(c);
//		cerr << P[i] << " " << r << endl;
	}
	area *= PI*(4/3.0);
	area = corner.x()*corner.y()*corner.z() - area;
	return area;
}

int main(int argc,char **argv){
#ifdef HOME
	freopen("in.in","r",stdin);
#endif
	for(int t = 1,n; scanf("%d",&n) == 1 && n != 0;t++) {
		point3d A,B;
		cin >> A >> B;
		loop(i,3) {
			double mn = min(A.coord[i],B.coord[i]);
			double mx = max(A.coord[i],B.coord[i]);
			A.coord[i] = mn;
			B.coord[i] = mx;
		}
		point3d C = B - A;
		point3d P[n];
		loop(i,n) {
			cin >> P[i];
			P[i] = P[i] - A;
		}

		int ord[n];
		loop(i,n) ord[i] = i;
		double ans = 1e18;
		do{
			point3d Q[n];
			loop(i,n) Q[i] = P[ord[i]];
			ans = min(ans,solve(Q,n,C));
		}while(next_permutation(ord,ord + n));
		printf("Box %d: %.0f\n",t,ans);
		puts("");
	}
	return 0;
}
#endif
