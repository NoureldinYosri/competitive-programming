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

double A[1 << 20],B[1 << 20];

double Pmx[1 << 20],Pmn[1 << 20];
int main(){
	int n;  double a,b,c,d,Sa = 0,Sb = 0,S;
	scanf("%d",&n);
	loop(i,n) scanf("%lf",Pmx + i);
	loop(i,n) scanf("%lf",Pmn + i);
	loop(i,n){
		S = Pmx[i] + Pmn[i];
		a = 1;
		b = Sa - S - Sb;
		c = Pmx[i] - Sa*S;
		d = b*b - 4*a*c;
		d = max(d,0.0);
		d = sqrt(d);		
		A[i] = (-b + d)/2.0/a;
		B[i] = S - A[i];
		Sa += A[i];
		Sb += B[i];
	}
	loop(i,n) printf("%.10lf%s",A[i],(i == n - 1) ? "\n": " ");
	loop(i,n) printf("%.10lf%s",B[i],(i == n - 1) ? "\n": " ");
	
	return 0;
}
