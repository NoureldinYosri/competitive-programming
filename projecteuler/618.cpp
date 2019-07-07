#ifdef INPROGRESS
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

const int MAXN = 46368;
ll F[25];
int prime[MAXN + 1];

int main(int argc,char **argv){
#ifdef HOME
	freopen("in.in","r",stdin);
#endif
	F[1] = 1;
	for(int i = 2;i <= 24;i++)
		F[i] = F[i - 1] + F[i - 2];
	prArr(F,25,ll);
	sieve(MAXN,prime);
	vi primes;
	for(int p = 2;p <= MAXN;p++)
		if(prime[p] == p)
			primes.pb(p);
	print(primes,int);
	return 0;
}
#endif
