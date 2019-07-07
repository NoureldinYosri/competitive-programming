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

const double PI = acos(-1);
typedef complex<double> point;
point P[100];
int n;

double solve(point O,double theta) {
	point w = polar(1.0,theta);
	double mn = 1e18,mx = -1e18;
	loop(i,n){
		point p = (P[i] - O) * w + O;
		mn = min(mn,p.real());
		mx = max(mx,p.real());
	}
	return mx - mn;
}

int main(int argc,char **argv){
#ifdef HOME
	freopen("in.in","r",stdin);
#endif
	for(int t = 1;scanf("%d",&n) == 1 && n;t++) {
		loop(i,n) {
			int x,y; scanf("%d %d",&x,&y);
			P[i] = point(x,y);
		}

		double ans = 1e18;
		loop(i,n) loop(j,i) {
			point O = (P[i] + P[j])/2.0;
			double theta = arg(P[i] - P[j]);
			ans = min(ans,solve(O,-theta));
			ans = min(ans,solve(O,PI/2-theta));
		}
		printf("Case %d: %.2f\n",t,ans);
	}
	return 0;
}
#endif
