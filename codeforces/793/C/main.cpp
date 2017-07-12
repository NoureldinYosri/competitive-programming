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

const int MAX = 100*1000 + 10;
typedef pair<ll,ll> pl;


auto cmp = [](const pl & a,const pl & b){
	return (a.xx*b.yy - a.yy*b.xx) < 0;
};






void normalize(pl & t){
	if(t.yy < 0) t.xx *= -1,t.yy *= -1;
	ll d = __gcd(abs(t.xx),abs(t.yy));
	t.xx /= d;
	t.yy /= d;
}

bool work(int x1,int x2,int rx,int vx,pl & t1,pl & t2){
	if(vx){
		t1 = mp((x1 - rx),vx);
		t2 = mp((x2 - rx),vx);
	}
	else if(rx <= x1 || rx >= x2) {
		return 0;
	}
	else {
		t1 = mp(0,1);
		t2 = mp(INT_MAX,1);
	}
	normalize(t1);
	normalize(t2);
	if(cmp(t2,t1)) t1.swap(t2);
	return 1;
}

ostream& operator << (ostream & st,const pl & p){
	st << setprecision(10) << p.xx*1.0/p.yy ;
	return st;
}

int main(){
	#ifndef ONLINE_JUDGE
		freopen("input.in", "r", stdin);
	#endif
	int x1,x2,y1,y2,n;
	scanf("%d",&n);
	scanf("%d %d %d %d",&x1,&y1,&x2,&y2);
	pl mn(INT_MAX,1),mx(0,1);
	loop(i,n){
		int rx,ry,vx,vy;
		scanf("%d %d %d %d",&rx,&ry,&vx,&vy);
		pl t1,t2,t3,t4;
		if(!work(x1,x2,rx,vx,t1,t2) || !work(y1,y2,ry,vy,t3,t4)){
			puts("-1");
			return 0;
		}
		if(cmp(t3,t1)) t1.swap(t3),t2.swap(t4);
		if(cmp(t2,t3)) {
			puts("-1");
			return 0;
		}
		pl S,E;
		S = max(t1,t3,cmp);
		E = min(t2,t4,cmp);
		mn = min(mn,E,cmp);
		mx = max(mx,S,cmp);
//		cerr << S << " " << E << endl;
	}
	if(cmp(mn,mx) || mn == mx) puts("-1");
	else printf("%.15f\n",mx.xx*1.0/mx.yy + 1e-10);
	return 0;
}
