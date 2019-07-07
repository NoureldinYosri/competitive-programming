#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define range(i,a,b) for(int i = (a);i <= (b);i++)
#define all(A) A.begin(),A.end()
#define pb push_back
#define mp make_pair
#define sz(A) ((int)A.size())
#define vi vector<int>
#define vd vector<double>
#define vp vector<pair<int,int> >
#define ll long long
#define pi pair<int,int>
#define popcnt(x) __builtin_popcountll(x)
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
using namespace std;

const int MAX = 100*1000 + 10;
typedef complex<double> point;
int X[MAX],Y[MAX],n;

int sgn(ll x) {
	return (x > 0) - (x < 0);
}

ll distSquared(pi a,pi b) {
	ll dx = a.first - b.first;
	ll dy = a.second - b.second;
	return dx*dx + dy*dy;
}
double dist(pi a,pi b) {
	return sqrt(distSquared(a,b));
}
bool leq(double x,double y) {
	return x < y || abs(x-y) < 1e-9;
}

double dist(point a,point b) {
	//x1*x2 - y1*y2
	point r = b-a;
	return sqrt(norm(r));
}

double getLowerBound(double x0) {
	double r = 0;
	loop(i,n) {
		double dx = X[i] - x0;
		double g = dx*dx/(2*Y[i]) + Y[i]/2.0;
		r = max(r,g);
	}
	return r;
}

double solveBS() {
	double s = 1e7,e = -1e7;
	loop(i,n) s = min(s,X[i] + 0.0),e = max(e,X[i] + 0.0);
	for(int i = 0;i < 200 && s < e;i++){
		double m1 = s + (e-s)/3;
		double m2 = m1 + (e-s)/3;
		if(getLowerBound(m1) < getLowerBound(m2)) e = m2;
		else s = m1;
	}
//	cerr << s << " " << e << " " << getLowerBound(s) << endl;
	return min(getLowerBound(s),getLowerBound(e));
}


double solve(){
	map<int,int> cnt;
	loop(i,n) cnt[sgn(Y[i])]++;
	if(cnt[-1] && cnt[1]) return -1;
	if(cnt[0] > 1) return -1;
	loop(i,n) Y[i] = abs(Y[i]);
	if(cnt[0]) {
		pi pivot;
		loop(i,n) if(Y[i] == 0) pivot = mp(X[i],Y[i]);
		return getLowerBound(pivot.first);
	}
	return solveBS();
}

int main(int argc,char **argv){
#ifdef HOME
	freopen("in.in","r",stdin);
#endif
	scanf("%d",&n);
	loop(i,n) scanf("%d %d",X + i,Y + i);
	printf("%.6f\n",solve());
	return 0;
}
