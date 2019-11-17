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


const double eps = 1e-12;
double B[200][400];
int n;
int ord[200];

void gauss(){
	loop(i,n) ord[i] = i;
	loop(i,n) loop(j,n) B[i][j + n] = i == j;
	loop(pivot,n) {
		int r = pivot;
		while(r < n && abs(B[r][pivot]) < eps) r++;
		assert(r < n);
		if(r != pivot) {
			loop(c,2*n) swap(B[r][c],B[pivot][c]);
			swap(ord[r],ord[pivot]);
		}
		r = pivot;
		double a = B[r][pivot];
		for(int c = pivot;c < 2*n;c++)
			B[r][c] /= a;
		for(int k = r+1;k < n;k++){
			double a = B[k][pivot];
			for(int c = pivot;c < 2*n;c++)
				B[k][c] -= B[r][c]*a;
		}
	}
//	loop(r,n){
//		prArr(B[r],2*n,double);
//	}
	for(int pivot = n-1;pivot >= 0;pivot--) {
		for(int r = pivot-1;r >= 0;r--){
			double a = B[r][pivot];
			for(int c = pivot;c < 2*n;c++)
				B[r][c] -= a*B[pivot][c];
		}
	}
//	loop(r,n){
//		prArr(B[r],2*n,double);
//	}

}

int main(){
	freopen("bujor.in", "r", stdin);
	freopen("bujor.out","w",stdout);
	int T; scanf("%d",&T);
	while(T--) {
		scanf("%d",&n);
		loop(i,n) loop(j,n) scanf("%lf",&B[i][j]);
		gauss();
		loop(i,n) loop(j,n) printf("%.9f%c",B[i][j+n]," \n"[j==n-1]);
	}
	return 0;
}
#endif
