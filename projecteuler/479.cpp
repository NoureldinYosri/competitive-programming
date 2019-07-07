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

const int mod = 1000000007;

ll bruteforce_S(int n) {
	ll ret = 0;
	for(int k = 1;k <= n;k++) {
		ll r = 1 - k*k,a = 1;
		for(int p = 1;p <= n;p++) {
			a *= r;
			ret += a;
		}
	}
	return ret;
}

int S(int n){
	int ret = 0;
	for(int k = 1;k <= n;k++) {
		int r = add(1,-mul(k,k,mod),mod);
		int s = 0;
		if(r <= 1) {
			s = n*r;
		}
		else {
			int a = add(powmod(r,n,mod),-1,mod);
			int b = powmod(r-1,mod-2,mod);
			s = mul(a,b,mod);
			s = mul(s,r,mod);
		}
		ret = add(ret,s,mod);
	}
	return ret;
}

int main(int argc,char **argv){
#ifdef HOME
	freopen("in.in","r",stdin);
#endif
	cout << S(1000*1000) << endl;
	return 0;
}
#endif
