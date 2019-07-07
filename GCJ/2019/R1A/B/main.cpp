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

int T,N,M;
int R[18],B[18];
int lowerG;
vi bases {5,7,11,13,17,4,9};

int read(){
	int x; cin >> x;
	if(x == -1) {
//		cerr << "read -1" << endl;
//		flush(cerr);
		exit(0);
	}
	return x;
}

void ask(int k) {
	loop(i,18) cout << (i ? " " : "") << bases[k];
	cout << endl;
	flush(cout);
	loop(i,18) R[i] = read();
//	prArr(R,18,int);
}

void step(int k){
	ask(k);
	int sG = 0;
	loop(i,18) sG += R[i];
	lowerG = max(lowerG,sG);
	B[k] = sG%bases[k];
}

int egcd(int a,int b,ll & x,ll & y,ll mod) {
	if(b == 0) {
		x = 1;
		y = 0;
		return a;
	}
	int d = egcd(b,a%b,x,y,mod);
	// x*b + y*(a - (a/b)*b) = d
	// x*b + y*a - (a/b)*y*b = d
	ll t = x;
	x = y;
	y = t-(a/b)*y;
//	x = (x%mod + mod)%mod;
//	y = (y%mod + mod)%mod;
	assert(x*a + b*y == d);
	return d;
}

int CRT(){
	int m = bases[0];
	ll x = B[0];
	for(int i = 1;i < 7;i++) {
		ll im,ip;
		int p = bases[i];
		ll r = B[i];
		egcd(m,p,im,ip,m*p);
		ll ox = x;
		x = p*x*ip + im*r*m;
		ll lcm = m*p;
		x = (x%lcm + lcm)%lcm;
		assert(x%p == r);
		assert(x%m == ox);
		assert(x <= M);
		m = lcm;
	}
	return x;
}

void solve(){
	lowerG = 1;
	loop(i,7) step(i);

	cout << CRT() << endl;
	flush(cout);
	read();
}

int main(int argc,char **argv){
#ifdef HOME
	freopen("in.in","r",stdin);
#endif
	cin >> T >> N >> M;
	while(T--) solve();
	return 0;
}
