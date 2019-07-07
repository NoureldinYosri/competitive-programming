#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
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

const int MAXN = 200*1000 + 10;
const int MAXA = MAXN*2;

int n;
int A[MAXN];
int ctr[3];
int prime[MAXA];
vi primes;

void readInput(){
	scanf("%d",&n);
	loop(i,n) {
		scanf("%d",A + i);
		ctr[A[i]]++;
	}
}

void sieve(){
	for(int p = 2;p < MAXA;p++)
		if(prime[p] == 0) {
			prime[p] = p;
			primes.push_back(p);
			for(ll j = p*(ll)p;j < MAXA;j += p)
				prime[j] = p;
		}
}


int main(int argc,char **argv){
#ifdef HOME
	freopen("in.in","r",stdin);
#endif
	sieve();
	readInput();
	loop(i,n) A[i] = 1;
	int c2 = ctr[2];
	int primeCount = 0;
	for(int i = 0,s = 0;i < n;i++) {
		s ++;
		if(prime[s] == s && n-i-1 >= c2) {
			primeCount += prime[s] == s;
			continue;
		}
		if(c2) {
			s ++;
			A[i] = 2;
			c2--;
		}
		primeCount += prime[s] == s;
	}
	loop(i,n) printf("%d%c",A[i]," \n"[i==n-1]);
//	cerr << primeCount << endl;
	return 0;
}
