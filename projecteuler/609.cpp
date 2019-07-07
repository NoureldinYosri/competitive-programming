#ifdef ACTIVE
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

const int MAXN = 1000*1000*100,MAXNUM = 5761455,MAXK = 12;
const int mod = 1000000007;

int add(int a,int b) {
	a += b;
	if(a >= mod) a -= mod;
	return a;
}
int mul(int a,int b) {
	return (a*1LL*b)%mod;
}

int not_prime[MAXN + 1],num[MAXN + 1];
int f[MAXN + 1];
int p[MAXNUM + 1][MAXK + 1];

void sieve(){
	not_prime[1] = 1;
	for(int i = 2;i <= MAXN;i++){
		num[i] = num[i - 1] + (not_prime[i] == 0);
		if(not_prime[i] == 0) {
			for(ll j = i*(ll)i;j <= MAXN;j += i)
				not_prime[j] = 1;
		}
	}
}

int Q[MAXK];
int q[MAXK];

int main(int argc,char **argv){
	sieve();
	f[1] = 1;
	int ans = 1;
	for(int i = 1;i <= MAXN;i++){
		int v = num[i];
		assert(v <= MAXNUM);
		f[i] = f[v] + not_prime[i];
		if(not_prime[i]) {
			q[0] = 0;
			for(int k = 0;k+1 < MAXK;k++)
				q[k + 1] = p[v][k];
			assert(p[v][MAXK-1] == 0);
		}
		else {
			for(int k = 0;k < MAXK;k++)
				q[k] = p[v][k];
		}
		loop(k,MAXK) Q[k] = add(Q[k],q[k]);
		q[not_prime[i]] = add(q[not_prime[i]],1);
		if(i <= MAXNUM) copy(q,q + MAXK,p[i]);
	}
	prArr(Q,MAXK,int);
	ans = 1;
	loop(i,MAXK) if(Q[i]) ans = mul(ans,Q[i]);
	cout << ans << endl;
	return 0;
}

//10: 648
//100: 38675815
#endif
