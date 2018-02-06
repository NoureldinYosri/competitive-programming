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
		st << fixed << setprecision(1) <<  "(" << n.real << " ," << n.imag << " )";
		return st;
	}

};


typedef num* poly;
const num one (1.0,0.0),zero(0.0,0.0);

int rev(int n,int l){
	char s[l + 1];
	for(int i = 0;i < l;i++) s[i] = '0';
	for(int i = 0;n;i++,n /= 2) s[i] = n%2 + '0';
	int ans = 0;
	for(int i = 0;i < l;i++) ans = (ans << 1) + (s[i] - '0');
	return ans;
}
int len(int n){
	int ans = 0;
	for(;n;n /= 2) ans++;
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
			for(int j = 0;j < m/2;j++){
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

const int MAXN = 1000*1000 + 10,MAXN2 = MAXN << 2;
num pA[MAXN2],fA[MAXN2],pB[MAXN2],fB[MAXN2],pC[MAXN2],fC[MAXN2];
int N2,n_,m_;
char A[MAXN],B[MAXN];
int H[MAXN];
ll n,m;

void computeH(){
	N2 = n_ << 1;
	while(N2 != LSOne(N2)) N2++;
	N2 <<= 1;

	for(char c = 'a';c <= 'z';c++) {
		for(int i = 0;i < N2;i++) pA[i] = pB[i] = zero;
		for(int i = 0;i < 2*n_;i++)
			pA[i] = num(A[i%n_] == c,0);
		for(int i = 0;i < m_;i++)
			pB[i] = num(B[m_-1-i] == c,0);

		fft(pA,fA,0,N2);
		fft(pB,fB,0,N2);
		for(int i = 0;i < N2;i++)
			fC[i] = fA[i]*fB[i];
		fft(fC,pC,1,N2);
		for(int i = 0;i < n_;i++)
			H[i] += round(pC[i + m_- 1].real);
	}
	for(int i = 0;i < n_;i++) H[i] = m_ - H[i];
//	prArr(H,n_,int);
}

int visTime[MAXN],pivot,LEN;
bool vis[MAXN];

void getCylce(){
	int i = 0,t = 0;
	memset(visTime,-1,sizeof visTime);
	while(visTime[i] == -1) {
		visTime[i] = t++;
		i = (i + m_)%n_;
	}
	pivot = i;
	LEN = t - visTime[i];
}

ll getCnt(int i) {
	if(i < pivot) return 1;
	ll N = n*n_ - m_ + 1;
	N -= pivot;
//	cerr << N << " " << LEN << endl;
	ll ret = N/(LEN * 1LL * m_);
	N %= (LEN * 1LL * m_);
//	cerr << N << endl;
	if((0LL + visTime[i] - visTime[pivot])*m_ < N) ret++;
	return ret;
}

int main(){
	#ifdef HOME
		freopen("in.in", "r", stdin);
	#endif
	scanf("%lld %lld",&n,&m);
	if(n < m) scanf("%s %s",A,B);
	else {
		swap(n,m);
		scanf("%s %s",B,A);
	}
	n_ = strlen(A);
	m_ = strlen(B);
	computeH();
	getCylce();

	ll ans = 0;
	for(int i = 0;!vis[i];i = (i + m_)%n_) {
		int v = H[i];
		ll cnt = getCnt(i);
//		cerr << i << ". " << v << " " << cnt << endl;
		ans += cnt*v;
		vis[i] = 1;
	}
	cout << ans << endl;

	return 0;
}
