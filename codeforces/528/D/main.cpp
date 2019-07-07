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
		st << setprecision(3) <<  "(" << n.real << " ," << n.imag << " )";
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



const int MAX = 1 << 19;
int n,m,k;
char U[1 << 20],V[1 << 20];
num IA[MAX],OA[MAX],IB[MAX],OB[MAX],IC[MAX],OC[MAX];

void old(){
	cin >> n >> m >> k >> U >> V;
	string alpha = "ATGC";
	vi cnt(n,0);
	int N = n;
	while(N != LSOne(N)) N++;
	N <<= 1;
	for(char c : alpha){
		fill(IA,IA + N,zero);
		fill(IB,IB + N,zero);
		int e = -1;
		loop(i,n) {
			if(U[i] == c) {
				e = max(e,max(0,i - k));
				for(;e < i;e++) IA[e] = one;
				e = i + k;
			}
			if(i <= e) IA[i] = one;
		}
//		print(A,num);
		loop(i,m) if(V[i] == c) IB[m - 1 - i] = one;
		fft(IA,OA,0,N);
		fft(IB,OB,0,N);
		loop(i,N) IC[i] = OA[i]*OB[i];
		fft(IC,OC,1,N);
		for(int i = m-1,j = 0;j <= n-m;i++,j++) {
			int v = round(OC[i].real);
			cnt[j] += v;
		}
	//	prArr(OC,N,num);
	}
	int ctr = 0;
	for(int x : cnt) ctr += x == m;
	cout << ctr << endl;
}

void New(){
	cin >> n >> m >> k >> U >> V;
	string alpha = "ATGC";
	vi cnt(n,0),aux(n,0);
	int N = n;
	while(N != LSOne(N)) N++;
	N <<= 1;
	for(char c : alpha){
		int target = 0;
		for(char cv : V) target += c == cv;
		fill(IA,IA + N,zero);
		fill(IB,IB + N,zero);
		loop(i,n) {
			if(U[i] == c)
				IA[i] = one;
		}
//		print(A,num);
		loop(i,m) if(V[i] == c) IB[m - 1 - i] = one;
		fft(IA,OA,0,N);
		fft(IB,OB,0,N);
		loop(i,N) IC[i] = OA[i]*OB[i];
		fft(IC,OC,1,N);
		for(int i = m-1,j = 0;j <= n-m;i++,j++) {
			int v = round(OC[i].real);
			cnt[j] += v;
		}
//		print(cnt,int);
		for(int i = 1;i < n;i++)
			cnt[i] += cnt[i - 1];
		for(int i = 0;i < n;i++) {
			int r = min(n-1,i+k);
			int l = max(0,i-k);
			int s = cnt[r] - (l ? cnt[l - 1] : 0);
			aux[i] += s >= target;
		}
		fill(all(cnt),0);
	//	prArr(OC,N,num);
	}
	int ctr = 0;
	for(int i = 0;i <= n-m;i++) ctr += aux[i] == 4;
	cout << ctr << endl;
}

int main(){
	#ifndef ONLINE_JUDGE
		freopen("in.in", "r", stdin);
	#endif
	New();
	return 0;
}
