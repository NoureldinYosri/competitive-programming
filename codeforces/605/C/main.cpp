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
#define popcnt(x) __builtin_popcount(x)
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

typedef pair<ll,ll> pl;
const int MAX = 100*1000 + 10;
pl P[MAX],target;
int n;

ll ccw(pl o,pl u,pl v){
	u.xx -= o.xx,u.yy -= o.yy;
	v.xx -= o.xx,v.yy -= o.yy;
	return u.xx*1LL*v.yy - u.yy *1LL*v.xx;
}

ll dot(pl u,pl v){
	return u.xx*1LL*v.xx + u.yy*1LL*v.yy;
}

int sgn(ll val){
	return (val > 0) - (val < 0);
}

bool inRange(int l,int r,int x){
	return l <= x && x <= r;
}

bool do_intersect(pl a,pl b,pl c,pl d){
	if(a.xx > b.xx) swap(a,b);
	if(c.xx > d.xx) swap(c,d);
	int s1 = sgn(ccw(a,b,c)),s2 = sgn(ccw(a,b,d));
	int s3 = sgn(ccw(c,d,a)),s4 = sgn(ccw(c,d,b));
	if(!s1 || !s2 || !s3 || !s4){
		bool ret = 0;
		if(!s1) ret |= inRange(a.xx,b.xx,c.xx);
		if(!s2) ret |= inRange(a.xx,b.xx,d.xx);
		if(!s3) ret |= inRange(c.xx,d.xx,a.xx);
		if(!s4) ret |= inRange(c.xx,d.xx,b.xx);
		return ret;
	}
	else return (s1 != s2) && (s3 != s4);
}

ostream& operator << (ostream & st,const pl & p) {
	st << "(" << p.xx << " ," << p.yy << ")";
	return st;
}

int main(){
	#ifndef ONLINE_JUDGE
		freopen("in.in", "r", stdin);
	#endif
	ll x = 0,y = 0;
	scanf("%d %lld %lld",&n,&target.xx,&target.yy);
	loop(i,n) {
		scanf("%lld %lld",&P[i].xx,&P[i].yy);
		x = max(x,P[i].xx);
		y = max(y,P[i].yy);
	}
	P[n++] = mp(x,0);
	P[n++] = mp(0,y);
	sort(P,P + n);
	n = unique(P,P + n) - P;
	vp CH;
	int siz = 0;
	loop(i,n){
		while(siz > 1 && ccw(P[i],CH[siz - 1],CH[siz - 2]) <= 0) {
			siz--;
			CH.pop_back();
		}
		CH.pb(P[i]);
		siz++;
	}
	for(int i = n-1;i >= 0;i--) {
		while(siz > 1 && ccw(P[i],CH[siz - 1],CH[siz - 2]) <= 0) {
			siz--;
			CH.pop_back();
		}
		CH.pb(P[i]);
		siz++;
	}
	n = sz(CH);
	pl o (0,0);
	double ans = 1LL << 60;
	loop(i,n) {
		if(ccw(o,CH[i],target) == 0) {
			ans = min(ans,hypot(target.xx,target.yy)/hypot(CH[i].xx,CH[i].yy));
		}
	}
	pl T = target;
	int g = __gcd(T.xx,T.yy);
	T.xx /= g;
	T.yy /= g;
	for(x = 1000*1000;x % T.xx;x++);
	int mul = x/T.xx;
	T.xx = x;
	T.yy *= mul;
/*
	for(auto p : CH) {
		cerr << p ;
	}
	cerr << endl;
	*/
	loop(i,n) {
		//cerr << CH[i] << " " << CH[(i + 1)%n] << " " << T << " " << do_intersect(CH[i],CH[i+1],o,T) << endl;
		if(do_intersect(CH[i],CH[(i + 1)%n],o,T)) {
			int dx = CH[(i + 1)%n].xx - CH[i].xx;
			int dy = CH[(i + 1)%n].yy - CH[i].yy;
			x = CH[i].xx,y = CH[i].yy;
			// (T.xx,T.yy) cross (x + l*dx,y + l*dy) = 0
			// T.xx * y + T.xx * l*dy - T.yy*x - T.yy*l*dx = 0
			// T.xx * y - T.yy*x = l*(T.yy*dx - T.xx*dy)
			ll b = ccw(o,T,CH[i]);
			ll a = -ccw(o,T,mp(dx,dy));
			if(!a) continue;
			double l = (b + 0.0)/a;
			double curx = x + dx*l,cury = y + dy*l;
			double lenT = hypot(target.xx,target.yy),lenP = hypot(curx,cury);
			ans = min(ans,lenT/lenP);
		}
	}
	printf("%.10f\n",ans);
	return 0;
}
