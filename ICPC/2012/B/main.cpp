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

double A[20],B[40];
int n,m;

double f(double x){
	double ret = 0;
	loop(i,m+1) ret += B[i]*pow(x,i + 1)/(i + 1);
	return PI*ret;
}

void preprocess(){
	memset(B,0,sizeof B);
	for(int i = 0;i <= 2*n;i++)
		for(int j = 0;j <= i ;j++)
			B[i] += A[j]*A[i - j];
	m = 2*n;
}

int main(){
	#ifndef ONLINE_JUDGE
		freopen("input.in", "r", stdin);
	#endif
	for(int t = 1;scanf("%d",&n) == 1;t++){
		memset(A,0,sizeof A);
		loop(i,n+1) scanf("%lf",A + i);
		preprocess();
		double xl,xh;int inc ;
		scanf("%lf %lf %d",&xl,&xh,&inc);
		double F = f(xh) - f(xl);
//		fprintf(stderr,"f(%lf) = %lf\n",xl,f(xl));
//		fprintf(stderr,"f(%lf) = %lf\n",xh,f(xh));

		double x0 = xl;
		vector<double> X;
		while(xl <= xh && sz(X) < 8){
			double s = xl,e = xh;
			double fl = f(xl);
			for(int bst = 0;bst < 100 && e - s > 1e-6;bst++){
				double m = s + (e - s)/2;
				double fm = f(m) - fl;
				if(fm >= inc) e = m;
				else s = m + 1e-6;
			}
			double fr = f(e)-fl;
			if(fr < inc && abs(fr - inc) > 1e-4) break;
			X.pb(e);
			xl = e;
		}
		printf("Case %d: %.2f\n",t,F);
		if(X.empty()) puts("insufficient volume");
		else {
			loop(i,sz(X)) printf("%.2f%c",X[i]-x0," \n"[i==sz(X)-1]);
		}
	}
	return 0;
}
