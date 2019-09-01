#ifdef ACTIVE
#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define all(A) A.begin(),A.end()
#define pb push_back
#define mp make_pair
#define sz(A) ((int)A.size())
typedef std::vector<int> vi;
typedef std::pair<int,int> pi;
typedef std::vector<pi> vp;
typedef long long ll;
#define popcnt(x) __builtin_popcount(x)
#define LSOne(x) ((x) & (-(x)))
#define print(A,t) cerr << #A << ": "; copy(all(A),ostream_iterator<t>(cerr," " )); cerr << endl
#define prArr(A,n,t)  cerr << #A << ": "; copy(A,A + n,ostream_iterator<t>(cerr," " )); cerr << endl
#define PRESTDIO() cin.tie(0),cerr.tie(0),ios_base::sync_with_stdio(0)
#define what_is(x) cerr << #x << " is " << x << endl
#define bit_lg(x) (assert(x > 0),__builtin_ffsll(x) - 1)
const double PI = acos(-1);
template<class A,class B>
std::ostream& operator << (std::ostream& st,const std::pair<A,B> p) {
	st << "(" << p.first << ", " << p.second << ")";
	return st;
}
#define tc() int T; scanf("%d",&T); for(int t = 1;t <= T;t++)
using namespace std;

const double inf = 1e9,EPS = 1e-12;
const int MAXN = 50;
struct point3d{
	int x,y,z;
};
ll square(ll x) {
	return x*x;
}
ll dist2(point3d A,point3d B) {
	ll res = 0;
	res += square(A.x - B.x);
	res += square(A.y - B.y);
	res += square(A.z - B.z);
	return res;
}
struct parabola{
	ll a,b,c;
	parabola(){a=b=c=0;}
	parabola(ll x,ll y,ll z):a(x),b(y),c(z){}
	parabola(point3d A,point3d vA,point3d B,point3d vB) {
		a = dist2(vA,vB);
		b 	= (A.x - B.x)*(vA.x - vB.x);
		b += (A.y - B.y)*(vA.y - vB.y);
		b += (A.z - B.z)*(vA.z - vB.z);
		b *= 2;
		c = dist2(A,B);
	}
	parabola operator - (const parabola & o) {
		return parabola(a-o.a,b-o.b,c-o.c);
	}
	pair<double,double> getZeros(){
		if(a) {
			ll d = b*b - 4*a*c;
			if(d < 0) return mp(-inf,-inf);
			double xl = (-b-sqrt(d))/(2.0*a);
			double xr = (-b+sqrt(d))/(2.0*a);
			if(xl > xr) swap(xl,xr);
			return mp(xl,xr);
		}
		if(b) {
			double x = -c*1.0/b;
			return mp(x,x);
		}
		return mp(-inf,-inf);
	}
	double eval(double x) {
		return a*x*x + b*x + c;
	}
};

point3d P[MAXN],V[MAXN];
int n;
parabola D[MAXN*MAXN];
int fr[MAXN*MAXN],to[MAXN*MAXN];
int m;
double dist[MAXN*MAXN];
vector<pair<double,pi>> stamps;
int W[MAXN],id[MAXN];

double leq(double a,double b) {
	return a < b || abs(a-b) < EPS;
}

inline void calc(double t) {
	for(int i = 0;i < m;i++)
		dist[i] = D[i].eval(t);
}

int find(int a) {
	return id[a] = (a == id[a]) ? a : find(id[a]);
}
bool connected(int a,int b) {
	return find(a) == find(b);
}
void join(int a,int b) {
	a = find(a),b = find(b);
	if(a == b) return;
	if(W[a] < W[b]) swap(a,b);
	W[a] += W[b];
	id[b] = a;
}


bool inMST[MAXN*MAXN];

bool buildMST(){
	static vi E,MST;
	E.clear();
	loop(i,m) E.push_back(i);
	sort(all(E),[](const int & a,const int & b) {
		return tie(dist[a],a) < tie(dist[b],b);
	});
	loop(i,n) W[i] = 1,id[i] = i;
	MST.clear();
	for(int i = 0;i < m;){
		int j = i;
		double w = dist[E[i]];
		while(j < m && dist[E[j]] == w) {
			int e = E[j];
			if(inMST[e]) {
				int a = fr[e],b = to[e];
				if(!connected(a,b)) {
					MST.push_back(e);
					join(a,b);
				}
			}
			j++;
		}
		for(;i < j;i++) {
			int e = E[i];
			int a = fr[e],b = to[e];
			if(!connected(a,b)) {
				MST.push_back(e);
				join(a,b);
			}
		}
	}
	bool areSame = 1;
	for(int e : MST) areSame &= inMST[e];
	if(!areSame) {
		loop(i,m) inMST[i] = 0;
		for(int e : MST) inMST[e] = 1;
	}
	return !areSame;
}

int solve(){
	m = 0;
	loop(i,n) loop(j,i) {
		fr[m] = i;
		to[m] = j;
		D[m++] = parabola(P[i],V[i],P[j],V[j]);
	}
	stamps.clear();
	loop(i,m) loop(j,i) {
		pair<double,double> t = (D[i] - D[j]).getZeros();
		if(!leq(t.first,0)) stamps.emplace_back(t.first,pi(i,j));
		if(!leq(t.second,0)) stamps.emplace_back(t.second,pi(i,j));
	}
	sort(all(stamps));
//	print(stamps,double);
	int ans = 1;
	calc(0);
	loop(i,m) inMST[i] = 0;
	buildMST();
	for(auto event: stamps) {
		double t = event.first;
		int e1 = event.second.first,e2 = event.second.second;
		if(!(inMST[e1] || inMST[e2])) continue;
		calc(t + 1e-7);
		loop(i,m) if(dist[i] != dist[i]) exit(0);
		ans += buildMST();
	}
	return ans;
}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	for(int t = 1;scanf("%d",&n) == 1;t++) {
		loop(i,n) {
			int x[3],v[3];
			loop(j,3) scanf("%d",x + j);
			loop(j,3) scanf("%d",v + j);
			P[i] = point3d{x[0],x[1],x[2]};
			V[i] = point3d{v[0],v[1],v[2]};
		}
		printf("Case %d: %d\n",t,solve());
	}
	return 0;
}
#endif
