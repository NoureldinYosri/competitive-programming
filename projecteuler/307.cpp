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

const int MAX = 20000 + 10;
const double PI = acos(-1),e = exp(1);
double logF[1 << 20];

double getlog(int n) {
	return logF[n];
}

double fact(int n) {
	if(n <= 20) {
		double ret = 1;
		loop(i,n) ret *= i+1;
		return ret;
	}
	return exp(getlog(n));
}

double solve(int n,int k) {
	vd L;
	double ret = 0;
	for(int one = 0;one <= k;one++) {
		int two = k - one;
		if(two&1) continue;
		two >>= 1;
		if(one + two > n) continue;
		double tmp = getlog(k) + getlog(n) - getlog(one) - getlog(two) - getlog(n - one - two) - k*log(n) - two*log(2);
		assert(tmp == tmp);
		L.pb(tmp);
	}
	double mx = *max_element(all(L));
	for(double l : L) {
		ret += exp(l - mx);
	}
	ret = mx + log(ret);
	return ret;
}


int main(int argc,char **argv){
#ifdef HOME
	freopen("in.in","r",stdin);
#endif
	for(int n = 1;n < (1 << 20);n++)
		logF[n] = logF[n - 1] + log(n);
	int n = 1000000,k = 20000;
//	n = 7,k = 3;
	double p = solve(n,k);
	// p*n!/C(n + k - 1,n - 1)
	// p*n!^2/(n + k - 1)! *k! / n
	double ans = 1 - exp(p);
	cout << fixed << setprecision(10) << ans << endl;

//	double EPS = 1;
//	int ctr = 0;
//	for(int n = 1;n < (1 << 20);n++) {
//		double stirling = 0.5*log(2*PI*n) + n*log(n/e);
//		double err = logF[n] - stirling;
//		if(err < EPS) {
//			cout << fixed << setprecision(9) << n << ": " << err << endl;
//			EPS /= 10;
//			ctr++;
//			if(ctr == 10) break;
//		}
//	}
	return 0;
}
#endif
