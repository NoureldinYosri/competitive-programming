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

int cI(int n){
	int u;
	for(u = n-2;u > 1;u--)
		if(mul(u,u,n) == 1)
			break;
	return u;
}


const int MAXN = 20*1000*1000;
int I[MAXN+1];
int prime[MAXN+1];
map<int,int> primes;
vi divs;

void factor(int u) {
	while(u > 1) {
		int p = prime[u];
		u /= p;
		primes[p] ++;
	}
}

void getDivs() {
	divs.clear();
	divs.pb(1);
	for(auto pe : primes) {
		int p = pe.first,e = pe.second;
		int s = 0,cnt = sz(divs);
		for(;e > 0;e--) {
			for(int i = 0;i < cnt;i++){
				ll v = divs[s + i]*1LL*p;
				if(v > MAXN) continue;
				divs.pb(v);
			}
			int ts = s + cnt;
			cnt = sz(divs) - s - cnt;
			s = ts;
		}
	}
}

int main(int argc,char **argv){
#ifdef HOME
	freopen("in.in","r",stdin);
#endif
	sieve(MAXN,prime);
	loop(i,MAXN+1) I[i] = 1;
	for(int x = 2;x < MAXN;x++) {
		primes.clear();
		factor(x-1);
		factor(x+1);
		getDivs();
//		print(divs,int);
		for(int m : divs){
			if(x < m-1) {
				int x2 = mul(x,x,m);
				if(x2 != 1){
					fprintf(stderr,"%d^2 = %d mod %d\n",x,x2,m);
					fflush(stderr);
				}
				assert(mul(x,x,m) == 1);
				I[m] = x;
			}
		}
		if(x%1000000 == 0) cout << "done with " << x/1000000 << " million" << endl;
	}
	assert(I[15] == 11);
	ll ans = 0;
	for(int n = 3;n <= MAXN;n++){
		ans += I[n];
//		assert(I[n] == cI(n));
	}
	cout << ans << endl;
	return 0;
}
#endif
