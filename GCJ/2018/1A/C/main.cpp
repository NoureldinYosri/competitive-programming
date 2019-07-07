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

const int MAX = 1000;
int n,P;
int A[MAX],B[MAX];

double leq(double a,double b) {
	return a < b || abs(a-b) < 1e-9;
}

double inrange(double x,double s,double e) {
	return leq(s,x) && leq(x,e);
}

bool same(double a,double b) {
	return abs(a-b) < 1e-9;
}

int main(int argc,char **argv){
#ifdef HOME
	freopen("in.in","r",stdin);
#endif
	int T; scanf("%d",&T);
	range(t,1,T) {
		scanf("%d %d",&n,&P);
		double ans = 0;
		int old = 0;
		vector<pair<double,double>> I;
		loop(i,n) {
			int a,b;
			scanf("%d %d",&a,&b);
			if(a > b) swap(a,b);
			old += 2*a + 2*b;
			double cmin = 2*a;
			double cmax = 2*sqrt(a*a + b*b);
			I.push_back(mp(cmin,cmax));
		}
		ans = old;
//		cerr << old << " " << P << endl;
//		for(auto p : I)
//			cerr << "\t" << p.xx << " " << p.yy << endl;
		if(P != old) {
			vector<pair<double,double>> C,tmp;
			sort(all(I));
			C.push_back(mp(0.0,0.0));
			for(auto p : I){
				for(int i = 0,L = sz(C);i < L;i++){
					auto q = C[i];
					C.push_back(mp(p.xx + q.xx,p.yy + q.yy));
				}
				sort(all(C));
				double s = 0,e = 0;
				for(auto q : C) {
					if(leq(q.xx,e))
						e = max(e,q.yy);
					else{
						tmp.push_back(mp(s,e));
						s = q.xx;
						e = q.yy;
					}
				}
				tmp.push_back(mp(s,e));
				C.swap(tmp);
				tmp.clear();
			}
			double best = 0;
			for(auto p : C) {
				if(inrange(P - ans,p.xx,p.yy))
					best = P - ans;
				if(leq(p.yy,P - ans))
					best = max(best,p.yy);
			}
			ans += best;
		}
		assert(leq(ans,P));
		printf("Case #%d: %.10f\n",t,ans);
	}
	return 0;
}
