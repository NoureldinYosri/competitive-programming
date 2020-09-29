#pragma GCC optimize ("O3")
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
using namespace std;


int n;
double K[1 << 20], C[1 << 20];
double X[1 << 20];

void solve(){
	double sum_k = 0, sum_kc = 0;
	loop(i, n) {
		sum_k += 1.0/K[i];
		sum_kc += K[i]*C[i];
	}
	if(sum_kc < 0){
		puts("-1");
		return ;
	}


	double lambda = 4*sum_kc/sum_k;
	
	loop(i, n) X[i] = pow(2*K[i], -2)*lambda - C[i];
		
	double F = 0;
	loop(i, n) F += sqrt(X[i] + C[i]);
	printf("%.10f", F);
	loop(i, n) printf(" %.10f", X[i]);
	puts("");
}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	int T; scanf("%d", &T);
	while(T--){
		scanf("%d", &n);
		loop(i, n) scanf("%lf", K + i);
		loop(i, n) scanf("%lf", C + i);
		solve();
	}
	return 0;
}
