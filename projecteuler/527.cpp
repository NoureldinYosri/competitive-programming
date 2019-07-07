#ifdef DONE
#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
#include "my_math.h"
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


map<ll,double> dp;

double B(ll n) {
	if(n <= 1) return n;
	if(dp.count(n)) return dp[n];
	ll m = (1 + n)/2;
	return dp[n] = 1 + (B(m-1)*(m-1) + B(n-m)*(n-m))/n;
}



// R(n) = 1 + 2/n^2 *sum i*R(i)
// (1 + 2/n)*R(n) = 1 + 2/n^2 * S(n)
// R(n + 1) = 1 + 2/(n + 1)^2 * S(n)
// S(n) = (R(n + 1) - 1)*(n+1)^2 / 2
// (1 + 2/n)*R(n) = 1 + (n + 1)^2/n^2 * (R(n + 1) - 1)
// ((1 + 2.0/n)*R(n) - 1)*n^2/(n + 1.0)^2 + 1 = R(n + 1)

map<int,double> mem;
double R(int n) {
	if(n <= 1) return n;
	if(mem.count(n)) return mem[n];
	double ret = 0;
	for(int u = 1;u < n;u++)
		ret += u*R(u);
	ret = 2*ret/(n*n) + 1;
	return mem[n] = ret;
}

int main(int argc,char **argv){
#ifdef HOME
	freopen("in.in","r",stdin);
#endif
//	cout << B(6) << endl;
//	for(int n = 1;n <= 20;n++)
//		cout << R(n) << endl;
//	double r = 1,h = 0;
//	for(int n = 1;n <= 1000000;n++) {
//		h += 1.0/n;
//		cout << 2*(n+1.0)/n * h - 3 << endl;
//	}
	ll n = 10000000000LL;
	cout << B(n) << endl;
	double euler = 0.57721566490153286060651209008240243;
	double h = log(n)/log(exp(1)) + euler + 1/(2.0*n) - 1/(n*12.0*n);
	double r = 2*(n+1.0)/n * h - 3;
	cout << r << endl;
	cout << fixed << setprecision(8) << r - B(n) << endl;
	return 0;
}
#endif
