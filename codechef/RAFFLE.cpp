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


const double eps = 1e-9;
int V[1 << 20];
int n, m;


bool work(int start, double & ans, bool debug){
	double sum = 0;
	int num = n - start;
	for(int i = start; i < n;i++) sum += pow(1.0/V[i], 1.0/(m-1));
	double lambda = pow((num-1)/sum, m-1);
	ans = 0;
	for(int i = start; i < n; i++){
		double p = 1 - pow(lambda/V[i], 1.0/(m-1));
		if(abs(p) < eps) p = 0;
		if(abs(p - 1) < eps) p = 1;
		if(debug) cerr << start << " " << V[i] << " " << p << endl;
		if(p < 0 || p > 1) return 0;
		ans += V[i]*(1 - pow(1 - p, m))/m;
	}
	return 1;
}

double solve(){
	sort(V, V + n);
	reverse(V, V + n);
	if(m == 1) return V[0];
	double sum = 0;
	loop(i, n) sum += pow(1.0/V[i], 1.0/(m-1));
	while(n > 1){
		double lambda = pow((n - 1)/sum, (m-1));
		double p = lambda/V[n-1];
		if(abs(p) < eps) p = 0;
		if(abs(p - 1) < eps) p = 1;
		if(p >= 0 && p <= 1) break;
		sum -= pow(1.0/V[n-1], 1.0/(m-1));
		n--;
	}
	
	double ans = 0;
	double lambda = pow((n-1)/sum, m-1);
	loop(i, n){
		double p = 1 - pow(lambda/V[i], 1.0/(m-1));
		if(p < 0 || p > 1) return 0;
		ans += V[i]*(1 - pow(1 - p, m))/m;
	}
	
	return ans;
}



int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	int T; scanf("%d", &T);
	while(T--){
		scanf("%d %d", &n, &m);
		loop(i, n) scanf("%d", V + i);
		printf("%.10f\n", solve());
	}
	return 0;
}
