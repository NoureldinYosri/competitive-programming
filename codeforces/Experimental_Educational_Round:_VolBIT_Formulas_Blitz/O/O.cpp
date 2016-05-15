#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define range(i,a,b) for(int i = (a);i <= (b);i++)
#define rrep(i,n) for(int i = (n);i >= 0;i--)
#define rran(i,a,b) for(int i = (b);i >= (a);i--)
#define step(i,a,b,d) for(int i = (a);i <= (b); i += d)
#define all(A) A.begin(),A.end()
#define PI acos(-1)
#define pb push_back
#define mp make_pair
#define sz(A) A.size()
#define len(A) A.length()
#define vi vector<int>
#define ll long long
#define pi pair<int,int>
#define point pair<double,double>
#define pl pair<ll,ll>
#define popcnt(x) __builtin_popcount(x)
#define LSOne(x) ((x) & (-(x)))
#define xx first
#define yy second
#define PQ priority_queue
#define print(A,t) cerr << #A << ": "; copy(all(A),ostream_iterator<t>(cerr," " )); cerr << endl
#define prp(p) cerr << "(" << (p).first << " ," << (p).second << ")";
#define prArr(A,n,t)  cerr << #A << ": "; copy(A,A + n,ostream_iterator<t>(cerr," " )); cerr << endl
#define pre() cin.tie(0),cerr.tie(0),ios_base::sync_with_stdio(0)
using namespace std;

struct vec{
	double x,y;
public:
	vec(){}
	vec(double x,double y):x(x),y(y){}
	vec operator + (const vec & o){
		return vec(x + o.x,y + o.y);
	}
	vec operator * (const double & c){
		return vec(c*x,c*y);
	}
	void PRINT(){
		printf("%.18f %.18f\n",x,y);
	}
};

int main(){
	double px,py,vx,vy,a,b,c,d;
	cin >> px>>py>>vx>>vy>>a>>b>>c>>d;
	vec v = vec(vx,vy),p = vec(px,py);
	v = v * (1.0/ hypot(v.x,v.y));
	vec per = vec(-v.y,v.x);
	vec out;
	out = p + v*b; out.PRINT();	
	out = p + per*(a/2.0); out.PRINT();		
	out = p + per*(c/2.0); out.PRINT();
	out = p + v*(-d) + per * (c/2); out.PRINT();	
	out = p + v*(-d) + per * (-c/2); out.PRINT();
	out = p + per*(-c/2.0); out.PRINT();
	out = p + per*(-a/2.0); out.PRINT();
	return 0;
}
