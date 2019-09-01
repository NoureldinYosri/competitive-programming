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


pi operator + (const pi & a,const pi & b) {
    return pi(a.first + b.first,a.second + b.second);
}
pi operator - (const pi & a,const pi & b) {
    return pi(a.first - b.first,a.second - b.second);
}

pi operator * (const int & c,const pi & v) {
    return pi(v.first*c,v.second*c);
}

int sgn(ll x) {
    return (x > 0) - (x < 0);
}


ll cross(pi o,pi a,pi b) {
    a.first -= o.first, a.second -= o.second;
    b.first -= o.first, b.second -= o.second;
    return a.first*(ll)b.second - a.second*(ll)b.first;
}

auto cmp = [](const pi & a,const pi & b) {
    if(a.second == 0) return a.first > 0;
    if(b.second == 0) return a.second > 0 && b.first < 0;
    if(sgn(a.second) == sgn(b.second)) return cross(pi(0,0),a,b) > 0;
    return a.second > 0;
};

double mag(pi p,bool takeRoot) {
    double L = p.first*(ll)p.first + p.second*(ll)p.second;
    if(takeRoot) L = sqrt(L);
    return L;
}

pi P[1 << 20];
int n;

struct Jaw{
    pi cur,nxt,dir;
    int i;
    Jaw(){i=0;}
    Jaw(int k,pi r) {
        dir = r;
        i = k;
        cur = P[i];
        nxt = P[(i+1)%n];
    }
    double getCos(){
        pi p = dir;
        pi q = nxt - cur;
        pi t = q - p;
        return (mag(p,0) + mag(q,0) - mag(t,0))/(2*mag(p,1)*mag(q,1));
    }
    pi getDir() {
        return nxt - cur - dir;
    }
    bool rotate(pi dr) {
        dir = dir + dr;
        pi t = cur + dir;
        return cross(cur,nxt,t) == 0;
    }
    void step(){
        cur = nxt;
        i = (i + 1)%n;
        nxt = P[(i+1)%n];
    }
    friend ostream& operator << (ostream & st,const Jaw & J) {
        st << "{" << J.cur << ", " << J.dir << "}";
        return st;
    }
};

double PointLineDist(pi p,pi r,pi q) {
    double ans = abs(cross(p,q,p + r));
    ans /= hypot(r.first,r.second);
    return ans;
}


void getOneSide(vp & U) {
    for(int i = 0;i < n;i++) {
        pi p = P[i];
        while(sz(U) > 1 && cross(U[sz(U)-2],U[sz(U)-1],p) >= 0) U.pop_back();
        U.push_back(p);
    }
}

void getConvexHull() {
    vp U,D;
    sort(P,P + n);
    getOneSide(U);
    reverse(P,P + n);
    getOneSide(D);
    reverse(all(U));
    reverse(all(D));
    U.pop_back();
    D.pop_back();
    n = 0;
    for(pi p : U) P[n++] = p;
    for(pi p : D) P[n++] = p;
//  for(int i = 0;i < n;i++)
//      cout << P[i] << " ";
//  cout << endl;
}

void init(Jaw S[4]){
	int minX = INT_MAX,minY = INT_MAX;
	int maxX = INT_MIN,maxY = INT_MIN;
	loop(i,n){
		minX = min(minX,P[i].first);
		minY = min(minY,P[i].second);
		maxX = max(maxX,P[i].first);
		maxY = max(maxY,P[i].second);
	}
	loop(i,n){
		if(P[i].first == minX) S[0] = Jaw(i,pi(0,-1));
		if(P[i].second == minY) S[1] = Jaw(i,pi(1,0));
		if(P[i].first == maxX) S[2] = Jaw(i,pi(0,1));
		if(P[i].second == maxY) S[3] = Jaw(i,pi(-1,0));
	}
}


bool solve(){
    if(scanf("%d",&n) != 1) return 0;
    loop(i,n) scanf("%d %d",&P[i].first,&P[i].second);
    getConvexHull();
    Jaw sides[4];
    init(sides);
    double C[4];
    double ans = 1e15;
    for(int q = 0;q < n;q++) {
    	loop(i,4) C[i] = sides[i].getCos();
    	int k = max_element(C,C + 4) - C;
    	pi d = sides[k].getDir();
    	loop(i,4) {
    		int j = (i + k)%4;
    		if(sides[j].rotate(d)) sides[j].step();
    		swap(d.first,d.second);
    		d.first *= -1;
    	}

//    	loop(i,4) cerr << sides[i] << " ";
//    	cerr << endl;
    	double h = PointLineDist(sides[0].cur,sides[0].dir,sides[2].cur);
    	double w = PointLineDist(sides[1].cur,sides[1].dir,sides[3].cur);
//    	cerr << h << " " << w << endl;
    	ans = min(ans,2*h + 2*w);
    }
    printf("%.10f\n",ans);
    return 1;
}

int main(){
#ifdef HOME
    freopen("in.in", "r", stdin);
#endif
    while(solve());
    return 0;
}

