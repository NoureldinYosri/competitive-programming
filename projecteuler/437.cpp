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

const int MAXN = 100000000;
int prime[MAXN+1];

int main(int argc,char **argv){
	sieve(MAXN,prime);
	int ctr = 0;
	int N = 10000;
	for(int p = 2;p <= N;p++)
		if(p == prime[p] && (p%10 == 1 || p%10 == 9)) {
			int s5 = Cipolla(5,p);
			if(mul(s5,s5,p) != 5) continue;
			int r2 = powmod(2,p-2,p);
			int g = mul(add(1,s5,p),r2,p);
			assert(mul(g,g,p) == add(1,g,p));
			ctr++;
		}
	cout << ctr << endl;
	return 0;
}
#endif
