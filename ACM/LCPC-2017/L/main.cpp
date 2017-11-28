#pragma GCC optimize ("O3")
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
const double PI = acos(-1);
using namespace std;

const double EPS = 1e-8;
int n,m;
int X[1 << 20],R[1 << 20];
int ord[1 << 20];
vi ST;

bool can(int circ,int p,double r) {
	double d = abs(X[p] - X[circ]);
	cerr << d << " vs " << r << endl;
	if(d > r) return 0;
	double ri = sqrt(r*r - d*d);
	cerr << "leads to " <<  ri << " vs " << R[p] << endl;
	return ri >= R[p];
}

bool can(double r) {
	int lst = -1;
	ST.clear();
	loop(j,n + m) {
		int i = ord[j];
		if(i >= n) {
			while(!ST.empty()) {
				if(can(i,ST.back(),r)) {
					cerr << i-n+1 << " takes " << ST.back() + 1 << endl;
					ST.pop_back();
				}
				else break;
			}
			if(!ST.empty()) return 0;
			lst = i;
		}
		else {
			if(lst != -1 && can(lst,i,r)) {
				cerr << lst-n+1 << " takes " << i + 1 << endl;
				continue;
			}
			lst = -1;
			ST.pb(i);
		}
	}

	return ST.empty();
}

void preprocess(){
	loop(i,n + m) ord[i] = i;
	sort(ord,ord + n  + m,[](const int & a,const int & b){
		return X[a] < X[b];
	});
}

double solve(){
	double s = 0,e = 3e9;
	for(int i = 0;i < 100 && e - s > EPS;i++) {
		double m = s + (e - s)/2;
		if(can(m)) e = m - EPS;
		else s = m + EPS;
	}
	return s;
}

int main(){
	freopen("syria.in", "r", stdin);
	int T; scanf("%d",&T);
	range(t,1,T) {
		scanf("%d %d",&n,&m);
		loop(i,n) scanf("%d %d",X + i,R + i);
		loop(i,m) scanf("%d",X + n + i);
		preprocess();
//		printf("%.6f\n",solve());
		cerr << can(5) << endl;
		break;
	}
	return 0;
}
