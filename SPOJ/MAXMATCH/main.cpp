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

struct num{
	long double real,imag;
public:
	num(){real=imag=0;}
	num(double a,double b){
		real = a;
		imag = b;
	}
	num operator /= (const double & c){
		this->real /= c;
		this->imag /= c;
		return *this;
	}
	num operator * (const double & c){
		return num(real*c,imag*c);
	}
	num operator + (const num & o){
		return num(real + o.real,imag + o.imag);
	}
	num operator - (const num & o){
		return num(real - o.real,imag - o.imag);
	}
	num operator * (const num & o){
		return num(real*o.real - imag*o.imag,real*o.imag + imag*o.real);
	}

};

long double real(const num & a){
	return a.real;
}

typedef vector<num> poly;
const num one = num(1.0,0.0),zero = num(0.0,0.0);

poly fft(poly I,int m,num w){
	if(m == 1) return I;
	poly even(m >> 1),odd(m >> 1),ret(m);
	for(int i = 0;i < m;i += 2) even[i >> 1] = I[i];
	for(int i = 1;i < m;i += 2) odd[i >> 1] = I[i];
	even = fft(even,m >> 1,w*w);
	odd = fft(odd,m >> 1,w*w);
	num root = one;
	for(int i = 0;2*i < m;i++){
		ret[i] = even[i] + root*odd[i];
		ret[i + m/2] = even[i] - root*odd[i];
		root = root*w;
	}
	return ret;
}

poly fft(poly I,bool inv){
	int m = sz(I);
	while(m != LSOne(m)) {
		I.pb(zero);
		m++;
	}
	if(!inv){
		loop(i,m) I.pb(zero);
		m <<= 1;
	}
	double theta = 2*PI/m;
	if(inv) theta *= -1;
	num w = num(cos(theta),sin(theta));
	I = fft(I,m,w);
	if(inv){
		loop(i,m) I[i] /= m;
	}
	return I;
}

poly operator * (poly A,poly B){
	int m = max(sz(A),sz(B));
	while(sz(A) != m) A.pb(zero);
	while(sz(B) != m) B.pb(zero);
	poly C(m);
	loop(i,m) C[i] = A[i]*B[i];
	return C;
}

char buffer[1 << 20];
int len;

int main(){
	#ifndef ONLINE_JUDGE
		freopen("in.in", "r", stdin);
	#endif
	scanf("%s",buffer);
	len = strlen(buffer);
	vi tot(len-1,0);
	for(char ch = 'a';ch <= 'c';ch++){
		poly A(len,zero),B(len,zero);
		loop(i,len) if(buffer[i] == ch) {
			A[i] = one;
			B[len - 1 - i] = one;
		}
		A = fft(A,0);
		B = fft(B,0);
		poly C = A*B;
		C = fft(C,1);
		for(int i = 0;i < len-1;i++)
			tot[i] += round(real(C[i + len]));
	}
	int mx = 0;
	for(int x : tot) mx = max(x,mx);
	printf("%d\n",mx);
	loop(i,len-1) if(tot[i] == mx) printf("%d ",i+1);
	puts("");
	return 0;
}
