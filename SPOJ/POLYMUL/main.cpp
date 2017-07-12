#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define range(i,a,b) for(int i = (a);i <= (b);i++)
#define all(A) A.begin(),A.end()
#define pb push_back
#define mp make_pair
#define sz(A) ((int)A.size())
#define vi vector<int>
#define vl vector<long long>
#define vd vector<double>
#define vp vector<pair<int,int> >
#define ll long long
#define pi pair<int,int>
#define pl pair<ll,ll>
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
const double PI = acos(-1);
using namespace std;

typedef complex<double> num;
typedef vector<num> poly;
const num zero = num(0,0);

poly fft(poly I,int m,num w){
	if(m == 1) return I;
	poly even,odd;
	for(int i = 0;i < m;i += 2) even.pb(I[i]);
	for(int i = 1;i < m;i += 2) odd.pb(I[i]);
	even = fft(even,m >> 1,w*w);
	odd = fft(odd,m >> 1,w*w);
	poly ret (m);
	num W = 1;
	for(int i = 0;2*i < m;i++){
		ret[i] = even[i] + W*odd[i];
		ret[i + m/2] = even[i] - W*odd[i];
		W *= w;
	}
	return ret;
}

poly fft(poly I,bool inv){
	int m = sz(I);
	while(m != LSOne(m)) {
		I.pb(zero);
		m++;
	}
	if(!inv) {
		for(int i = 0;i < m;i++) I.pb(zero);
		m <<= 1;
	}

	double theta = 2*PI/m;
	if(inv) theta *= -1;
	num w = polar(1.0,theta);
	I = fft(I,m,w);
	if(inv) {
		for(int i = 0;i < m;i++) I[i] /= m;
	}
	return I;
}

int main(){
	#ifndef ONLINE_JUDGE
		freopen("in.in", "r", stdin);
	#endif
	int T; scanf("%d",&T);
	while(T--){
		int n; scanf("%d",&n);
		poly A(n+1),B(n+1);
		loop(i,n+1) {
			int x; scanf("%d",&x);
			A[i].real(x);
		}
		loop(i,n+1) {
			int x; scanf("%d",&x);
			B[i].real(x);
		}
		A = fft(A,0);
		B = fft(B,0);
		poly C(sz(A));
		for(int i = 0;i < sz(A);i++)
			C[i] = A[i]*B[i];
		C = fft(C,1);
		for(int i = 0;i <= 2*n;i++){
			ll c = round(real(C[i]));
			printf("%lld%c",c," \n"[i==2*n]);
		}
	}
	return 0;
}
