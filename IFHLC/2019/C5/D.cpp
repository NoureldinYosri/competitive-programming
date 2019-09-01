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

const int MAX = 2000 + 10;
int X[MAX],Y[MAX],R[MAX],n;
pair<double,pi> E[MAX*MAX];

double dist(double x,double y){
	return sqrt(x*x + y*y);
}

double cost(int a,int b) {
	return dist(X[a]-X[b],Y[a]-Y[b]) - R[a] - R[b];
}


int id[MAX],W[MAX];

int find(int a) {
	return id[a] = (a == id[a]) ? a : find(id[a]);
}
double join(int a,int b,double w) {
	a = find(a),b = find(b);
	if(a == b) return 0;
	if(W[a] < W[b]) swap(a,b);
	W[a] += W[b];
	id[b] = a;
	return w;
}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	scanf("%d",&n);
	int m = 0;
	loop(i,n) {
		scanf("%d %d %d",X + i,Y + i,R + i);
		loop(j,i) E[m++] = mp(cost(i,j),pi(i,j));
		id[i] = i;
		W[i] = 1;
	}
	sort(E,E + m);
	double ans = 0;
	loop(e,m) ans += join(E[e].second.first,E[e].second.second,E[e].first);
	printf("%.10f\n",ans);
	return 0;
}
#endif
