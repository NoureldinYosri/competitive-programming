#ifdef ACTIVE
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
#define vp vector<pair<double,double> >
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

const double NaN = nan("");
const double PI = acos(-1);
const double EPS = 1e-9;
const int MAX = 1 << 20;
int n,psi;
int X[MAX],Y[MAX];
double Xs[MAX];

bool end(){
	scanf("%d %d",&n,&psi);
	return n == 0 && psi == 0;
}

void read(){
	for(int i = 1;i <= n;i++)
		scanf("%d %d",X + i,Y + i);
	n++;
}

bool correct(){
	for(int i = 0;i+1 < n;i++)
		if(X[i] > X[i+1])
			return 0;
	return 1;
}

bool leq(double a,double b) {
	return a <= b || abs(a-b) < EPS;
}


double to_deg(double x) {
	const double r = 180/PI;
	return r*x;
}


const int MAXA = 180*1000;
double cC[MAXA+1],cS[MAXA+1];
double ccC[MAXA+1],ccS[MAXA+1];

void init(){
	for(int i = 0;i <= MAXA;i++){
		double t = i*PI/MAXA;
		ccC[i] = cos(t),ccS[i] = sin(t);
		cC[i] = cos(-t),cS[i] = sin(-t);
	}
}


bool valid(int t,double *C,double *S) {
	loop(i,n) Xs[i] = X[i]*C[t] - Y[i]*S[t];
	loop(i,n-1)
		if(!leq(Xs[i],Xs[i+1]))
			return 0;
//	cerr << t << ": ";
//	prArr(Xs,n,double);
	return 1;
}

int solveClock(){
	double *C = cC,*S = cS;
	int ret = -1;
	for(int i = 0;i < MAXA;i += 10){
		if(valid(i,C,S)){
			ret = i;
			break;
		}
	}
	if(ret <= 0) return ret;
	for(int i = 0;i < 10;i++)
		if(valid(ret-9+i,C,S))
			return ret-9+i;
	assert(0);
}
int solveCounter(){
	double *C = ccC,*S = ccS;
	int ret = -1;
	for(int i = 0;i < MAXA;i += 10){
		if(valid(i,C,S)){
			ret = i;
			break;
		}
	}
	if(ret <= 0) return ret;
	for(int i = 0;i < 10;i++)
		if(valid(ret-9+i,C,S))
			return ret-9+i;
	assert(0);
}

int solve(double & ang,char *dir) {
	if(correct()) return 2;
	int a = solveClock();
	int b = solveCounter();
	if(a == -1 && b == -1) return 0;
	bool take_a = 0;
	if(a != -1 && b != -1) take_a = a <= b;
	else if(a != -1) take_a = 1;
	if(take_a){
		ang = a;
		strcpy(dir,"clockwise");
	}
	else {
		ang = b;
		strcpy(dir,"counterclockwise");
	}
	ang /= 1000;
	return 1;
}

void bf(){
	double ang;
	char dir[50];
	int res = solve(ang,dir);
	ang = max(ang,0.0);
	if(res == 0) puts("Unacceptable");
	else if(res == 2) puts("Acceptable as proposed");
	else printf("Acceptable after %s rotation of %.2f degrees\n",dir,ang);
}

double inv_tan(double dx,double dy,double s,double e) {
	double theta = atan2(dy,dx);
	if(leq(s,theta) && leq(theta,e)) return theta;
	return NaN;
}


int main(int argc,char **argv){
#ifdef HOME
	freopen("in.in","r",stdin);
#endif
	init();
	for(int cn = 1;!end();cn++) {
		read();
		printf("Case %d: ",cn);
		bf();
		puts("");
	}
	return 0;
}
#endif
