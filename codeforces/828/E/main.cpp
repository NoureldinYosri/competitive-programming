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
	friend ostream& operator << (ostream & st,const num & n)  {
		st << setprecision(3) <<  "(" << ((abs(n.real) < 1e-15) ? 0 : n.real)
				<< " ," << ((abs(n.imag) < 1e-15) ? 0 : n.imag) << " )";
		return st;
	}

};


typedef num* poly;
const num one (1.0,0.0),zero(0.0,0.0);

int rev(int n,int l){
	char s[l + 1];
	for(int i = 0;i < l;i++) s[i] = '0';
	for(int i = 0;n;i++,n >>= 1) s[i] = (n & 1) + '0';
	int ans = 0;
	for(int i = 0;i < l;i++) ans = (ans << 1) + (s[i] - '0');
	return ans;
}
int len(int n){
	int ans = 0;
	for(;n;n >>= 1) ans++;
	return ans;
}

void bit_rev(poly IN,poly OUT,int m){
	int l = len(m)-1;
	for(int i = 0;i < m;i++){
		OUT[rev(i,l)] = IN[i];
	}
}

void fft(poly IN,poly OUT,bool inv,int n){
	bit_rev(IN,OUT,n);
	for(int s = 1,lg = len(n) - 1;s <= lg;s++){
		int m = (1 << s);
		double theta = 2*PI/m;
		if(inv) theta *= -1;
		num wm = num(cos(theta),sin(theta));
		for(int k = 0;k < n;k += m){
			num w = one;
			for(int j = 0;(j << 1) < m;j++){
				num t = w*OUT[k + j + m/2];
				num u = OUT[k + j];
				OUT[k + j] = u + t;
				OUT[k + j + m/2] = u - t;
				w = w*wm;
			}
		}
	}
	if(inv) for(int i = 0;i < n;i++) OUT[i] /= n;
}

int preprocess(poly p,int n){
	while(n != LSOne(n)) p[n++] = zero;
	loop(i,n) p[i + n] = zero;
	n <<= 1;
	return n;
}

char buffer[1 << 20];
const int MAX = 1 << 20;
num V[MAX],K[MAX],VK[MAX];
num cV[MAX],cK[MAX],cVK[MAX];
int cnt[1 << 20];
int n,N;
vi ans;

int main(){
	#ifndef ONLINE_JUDGE
		freopen("in.in", "r", stdin);
	#endif
	int T; scanf("%d",&T);
	while(T--){
		scanf("%d",&n);
		scanf("%s",buffer);
		loop(i,n) {
			V[i] = (buffer[i] == 'V') ? one : zero;
			K[n-1-i] = (buffer[i] == 'K') ? one : zero;
		}
		N = n;
		while(N != LSOne(N)) N++;
		N <<= 1;
		loop(i,N - n) {
			V[i + n] = zero;
			K[i + n] = zero;
		}
		fft(V,cV,0,N);
		fft(K,cK,0,N);
		loop(i,N) cVK[i] = cV[i] * cK[i];
		fft(cVK,VK,1,N);
		fill(cnt,cnt + N,0);
		loop(i,N) cnt[abs(n-1-i)] |= round(VK[i].real) != 0;
		ans.clear();
		for(int i = 1;i <= n;i++) {
			bool cond = 1;
			for(int j = i;j <= n;j += i)
				cond = cond && !cnt[j];
			if(cond) ans.pb(i);
		}
		printf("%d\n",sz(ans));
		loop(i,sz(ans)) printf("%d%c",ans[i]," \n"[i==sz(ans)-1]);
	}
	return 0;
}
