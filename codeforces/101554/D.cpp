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

const int MAX = 100*1000 + 10;
pi I[MAX],P[MAX];
int n;

ll cross(pi o,pi a,pi b){
	a.first -= o.first,a.second -= o.second;
	b.first -= o.first,b.second -= o.second;
	return a.first*(ll)b.second - a.second*b.first;
}
ll sgn(ll x) {
	return (x > 0) - (x < 0);
}

vector<pi> getHull(){
	vector<pi> H;
	loop(i,n) {
		pi p = I[i];
		while(sz(H) > 1 && sgn(cross(H[sz(H)-2],H[sz(H)-1],p)) >= 0) H.pop_back();
		H.push_back(p);
	}
	return H;
}

void getConvexHull(){
	sort(I,I + n);
	n = unique(I,I + n) - I;

	vector<pi> U = getHull();
	U.pop_back();

	reverse(I,I + n);

	vector<pi> D = getHull();
	D.pop_back();

	n = 0;
	for(auto p : U) P[n++] = p;
	for(auto p : D) P[n++] = p;
	reverse(P,P + n);
}

pi operator + (const pi & a,const pi & b) {
    return pi(a.first + b.first,a.second + b.second);
}
pi operator - (const pi & a,const pi & b) {
    return pi(a.first - b.first,a.second - b.second);
}

pi operator * (const int & c,const pi & v) {
    return pi(v.first*c,v.second*c);
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

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	scanf("%d",&n);
	loop(i,n) scanf("%d %d",&I[i].first,&I[i].second);
	getConvexHull();
	if(n <= 1) {
		puts("0");
		return 0;
	}
	else if(n == 2) {
		printf("%.10f\n",mag(P[0]-P[1],1));
		return 0;
	}
	Jaw J[2];
	J[0] = Jaw(max_element(P,P + n,[](const pi & a,const pi & b) {
		return a.first < b.first;
	}) - P,pi(0,1));
	J[1] = Jaw(min_element(P,P + n,[](const pi & a,const pi & b) {
		return a.first < b.first;
	}) - P,pi(0,-1));

//	loop(i,n) cout << P[i] << " ";
//	cout << endl;
//	cout << J[0].i << " " << J[1].i << endl;

	double ans = 0;
	double C[2];
//	loop(i,n) loop(j,i) cout << P[i] << " " << P[j] << " " << mag(P[i] - P[j],1) << endl;
	loop(i,n){
		ans = max(ans,mag(P[J[0].i] - P[J[1].i],0));
//		loop(j,2) cout << P[J[0].i] << " " << P[J[1].i] << endl;
		loop(j,2) C[j] = J[j].getCos();
		int c = max_element(C,C + 2) - C;
		pi dir = J[c].getDir();
		loop(j,2) {
			int sgn = 2*(j == c) - 1;
			if(J[j].rotate(sgn*dir))
				J[j].step();
		}
	}
	ans = sqrt(ans);
	printf("%.10f\n",ans);
	return 0;
}
