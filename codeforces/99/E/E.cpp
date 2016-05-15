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


struct state{
	int x,h;
	double l,r;
public:
	state(){}
	state(int x,int h):x(x),h(h),l(-1){}
	state(int x,int h,double a,double b):x(x),h(h),l(a),r(b){}
	bool is_tree(){return l != -1;}
};

int n,m;
state landmark[1 << 20];
double ST[1 << 20];

void build(int node,int s,int e){
	ST[node] = 1;	
	if(s == e) return;
	int m = (s + e) >> 1,left = node << 1,right = left | 1;
	build(left,s,m);
	build(right,m + 1,e);
}

void update(int node,int s,int e,int l,int r,double p){
	if(l <= s && e <= r) {
		ST[node] *= p;
		return ;
	}
	int m = (s + e) >> 1,left = node << 1,right = left | 1;
	if(r <= m) return update(left,s,m,l,r,p);
	if(m  < l) return update(right,m + 1,e,l,r,p);
	update(left,s,m,l,m,p);
	update(right,m + 1,e,m + 1,r,p);
}

double query(int node,int s,int e,int x){
	if(s == e) return ST[node];
	int m = (s + e) >> 1,left = node << 1,right = left | 1;
	if(x <= m) return ST[node] * query(left,s,m,x);
	else return ST[node] * query(right,m + 1,e,x);
}

bool cmp (const state & s1,const state & s2){return s1.x < s2.x;}
bool cmp1 (const state & s1,const int & a){return s1.x < a;}
bool cmp2 (const int & a,const state & s1){return a < s1.x;}

int main(){
	int a,b,c,d;
	scanf("%d %d",&n,&m);
	loop(i,n) {
		scanf("%d %d %d %d",&a,&b,&c,&d);
		landmark[i] = state(a,b,c / 100.0,d / 100.0);
	}
	loop(i,m) {
		scanf("%d %d",&a,&b);
		landmark[i + n] = state(a,b);
	}
	n += m;
	build(1,0,n - 1);
	sort(landmark ,landmark + n,&cmp);
	/*loop(i,n){
		if(landmark[i].is_tree()) printf("tree @%d with h = %d and l = %.2f and r = %.2f\n",landmark[i].x,landmark[i].h,landmark[i].l,landmark[i].r);
		else printf("mush @%d with magic = %d\n",landmark[i].x,landmark[i].h);
	}*/
	loop(i,n){
		if(!landmark[i].is_tree()) continue;
		auto l = lower_bound(landmark,landmark + i,landmark[i].x - landmark[i].h,&cmp1) - landmark;
		auto u = lower_bound(landmark,landmark + i,landmark[i].x,&cmp1) - landmark - 1;
		if(l <= u) update(1,0,n - 1,l,u,1 - landmark[i].l);
		auto r = upper_bound(landmark + i,landmark + n,landmark[i].x + landmark[i].h,&cmp2) - landmark - 1;
		u = upper_bound(landmark + i,landmark + n,landmark[i].x,&cmp2) - landmark;
		if(u <= r) update(1,0,n - 1,u,r,1 - landmark[i].r);
	}
	double ans = 0.0;
	loop(i,n){
		if(landmark[i].is_tree()) continue;
		ans += landmark[i].h * query(1,0,n - 1,i);
	}
	printf("%.10f\n",ans);
	return 0;
}
