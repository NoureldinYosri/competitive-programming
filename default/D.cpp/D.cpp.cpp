#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define range(i,a,b) for(int i = (a);i <= (b);i++)
#define rrep(i,n) for(int i = (n);i >= 0;i--)
#define rran(i,a,b) for(int i = (b);i >= (a);i--)
#define step(i,a,b,d) for(int i = (a);i <= (b); i += d)
#define all(A) A.begin(),A.end()
#define pb push_back
#define mp make_pair
#define sz(A) A.size()
#define len(A) A.length()
#define print(A,t) cout << #A << ": "; copy(all(A),ostream_iterator<t>(cout," " )); cout << endl
#define pi pair<int,int>
#define point pi
#define vi vector<int>
#define ll long long
#define pl pair<ll,ll>
#define pre() cin.tie(0),cout.tie(0),ios_base::sync_with_stdio(0)
#define popcnt(x) __builtin_popcount(x)
#define LSOne(x) ((x) & (-(x)))
#define xx first
#define yy second
#define prp(p) cout << "(" << (p).first << " ," << (p).second << ")";
#define prArr(A,n,t)  cout << #A << ": "; copy(A,A + n,ostream_iterator<t>(cout," " )); cout << endl
using namespace std;

pair<pi,int> C[2];

double f(int x,int y){
	//cerr << x*x << " " << y*y << " " << sqrt(x*x+y*y) << endl;
	return sqrt(x*x+y*y);
}

int main(){
	loop(i,2) cin >> C[i].xx.xx >> C[i].xx.yy >> C[i].yy;
	//loop(i,2) cerr << C[i].xx.xx << " " << C[i].xx.yy <<" "<< C[i].yy << endl;
	double ans = 0;
	if(hypot(C[0].xx.xx - C[1].xx.xx,C[0].xx.yy - C[1].xx.yy) < C[0].yy + C[1].yy){
		double d = f(C[0].xx.xx-C[1].xx.xx,C[0].xx.yy-C[1].xx.yy),
			l = (C[0].yy*C[0].yy-C[1].yy*C[1].yy+d*d)/d/2.0,
			h = sqrt(C[0].yy*C[0].yy-l*l);
		//cerr << C[0].yy << " " << l << endl;
		double x1 =  l/d*(C[1].xx.xx-C[0].xx.xx)+C[0].xx.xx,x2=x1;
		double z = h/d * (C[1].xx.yy-C[0].xx.yy);
		x1 += z; x2 -= z;
		z = h/d*(C[1].xx.xx-C[0].xx.xx);
		double y1 = l/d*(C[1].xx.yy-C[0].xx.yy)+C[0].xx.yy,y2=y1;
		y1 += z;
		y2 -= z;
		//cerr << h << " " << l << " " << d << endl;
		cerr << x1 << " " << y1 << endl << x2 << " " << y2 << endl;
		double c1 = (2*C[0].yy*C[0].yy - hypt(x1-x2,y1-y2))/2.0/C[0].yy/C[0].yy,
			c2 = (2*C[1].yy*C[1].yy - hypt(x1-x2,y1-y2))/2.0/C[1].yy/C[1].yy;
		double t1 = acos(c1),t2 = acos(c2);
		if(t1 < 0) t1 += 2*acos(-1);
		if(t2 < 0) t2 += 2*acos(-1);
		if(t1 > acos(-1)) ans += pi*C[0]*C[0] - 0.5*
		ans = 0.5*C[0].yy*C[0].yy*sin(t1)+0.5*C[1].yy*C[1].yy*sin(t1);
	} 
	printf("%.6f\n",ans);
	return 0;
}
