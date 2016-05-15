#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define range(i,a,b) for(int i = (a);i <= (b);i++)
#define rrep(i,n) for(int i = (n);i >= 0;i--)
#define rran(i,a,b) for(int i = (b);i >= (a);i--)
#define step(i,a,b,d) for(int i = (a);i <= (b); i += d)
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

pl I[1 << 20];
ll x,y;

double f(pl  u,pl  v){
	point s = mp(v.xx - u.xx + 0.0,v.yy - u.yy + 0.0),t = mp(x - u.xx + 0.0,y - u.yy + 0.0);
	double r = (s.xx * t.xx + s.yy * t.yy + 0.0)/(s.xx * s.xx + s.yy * s.yy + 0.0);
	point proj = s; proj.xx *= r; proj.yy *= r;
	if(r > 1 || abs(r - 1) < 1e-15 || r < 0 || abs(r) < 1e-15) return LLONG_MAX;
	proj.xx += u.xx;
	proj.yy += u.yy;
	return pow(hypot(proj.xx - x,proj.yy - y),2.0);
}

int main(){
	int n; ll x1,y1;
	scanf("%d",&n);
	scanf("%I64d %I64d",&x,&y);
	double r_min = LLONG_MAX; ll r_max = 0;
	loop(i,n){
		scanf("%I64d %I64d",&x1,&y1);
		I[i].xx = x1,I[i].yy = y1;			
		ll d = (x - x1)*(x - x1) + (y - y1)*(y - y1);
		r_max = max(r_max,d);
		r_min = min(r_min,d+0.0);
	}
	loop(i,n) r_min = min(r_min,f(I[i],I[(i + 1)%n]));
	printf("%.15f\n",PI*(r_max - r_min));
	return 0;
}
