#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define range(i,a,b) for(int i = (a);i <= (b);i++)
#define rrep(i,n) for(int i = (n);i >= 0;i--)
#define rran(i,a,b) for(int i = (b);i >= (a);i--)
#define step(i,a,b,d) for(int i = (a);i <= (b); i += d)
#define all(A) A.begin(),A.end()
#define PI acos(-1)
#define pb push_back
#define sz(A) A.size()
#define len(A) A.length()
#define vi vector<int>
#define ll long long
#define pi pair<int,int>
#define pl pair<ll,ll>
#define popcnt(x) __builtin_popcount(x)
#define LSOne(x) ((x) & (-(x)))
#define PQ priority_queue
#define print(A,t) cerr << #A << ": "; copy(all(A),ostream_iterator<t>(cerr," " )); cerr << endl
#define prp(p) cerr << "(" << (p).first << " ," << (p).second << ")";
#define prArr(A,n,t)  cerr << #A << ": "; copy(A,A + n,ostream_iterator<t>(cerr," " )); cerr << endl
#define pre() cin.tie(0),cerr.tie(0),ios_base::sync_with_stdio(0)
using namespace std;


struct point{
	double xx,yy;
public:
	point(){}
	point(double x,double y):xx(x),yy(y){}	
};

point P[300];
int n;
double r = 2.5;


point operator * (const point & p1,const double & sc)  {
	return point(p1.xx*sc,p1.yy*sc);
}

point operator / (const point & p1,const double & sc)  {
	return point(p1.xx/sc,p1.yy/sc);
}

point operator * (const double & sc,const point & p1)  {
	return p1 * sc;
}


point operator + (const point p1 ,const point & p2) {
	return point(p1.xx + p2.xx,p1.yy + p2.yy);
}

point operator - (const point p1 ,const point & p2) {
	return p1 + (-1 * p2);
}


int main(){
	n = 0; int ans = 1;
	while(scanf("%lf %lf",&P[n].xx,&P[n].yy) == 2) n++;
	loop(j,n) loop(i,j){
		point vec = P[j] - P[i];
		double L = hypot(vec.xx,vec.yy);
		double h = r*r - L*L/4.0;
		if(abs(h) < 1e-15) h = 0.0;
		if(h < 0) continue;
		h = sqrt(h);
		vec = vec/L;
		point perp; perp.xx = vec.yy,perp.yy = -vec.xx;
		point O; 
		O = P[i] + vec*L/2 + perp*h;
		int ctr = 0;
		loop(k,n){
			point v = P[k] - O;
			double d = hypot(v.xx,v.yy);
			if(d < r || abs(d - r) < 1e-15) ctr++;	
		}	
		ans = max(ans,ctr);
		O = P[i] + vec*L/2 - perp*h;
		ctr = 0;
		loop(k,n){
			point v = P[k] - O;
			double d = hypot(v.xx,v.yy);
			if(d < r || abs(d - r) < 1e-15) ctr++;	
		}	
		ans = max(ans,ctr);
	}
	printf("%d\n",ans);
	return 0;
}
