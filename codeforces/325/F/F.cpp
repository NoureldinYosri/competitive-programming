#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define range(i,a,b) for(int i = (a);i <= (b);i++)
#define rrep(i,n) for(int i = (n);i >= 0;i--)
#define rran(i,a,b) for(int i = (b);i >= (a);i--)
#define step(i,a,b,d) for(int i = (a);i <= (b); i += d)
#define all(A) A.begin(),A.end()
#define PI acos(-1)
#define pb push_back
#define mp make_pair
#define sz(A) A.size()
#define len(A) A.length()
#define vi vector<int>
#define ll long long
#define pi mypair<int>
#define point mypair<double>
#define pl mypair<ll>
#define popcnt(x) __builtin_popcount(x)
#define LSOne(x) ((x) & (-(x)))
#define xx first
#define yy second
#define PQ priority_queue
#define print(A,t) cerr << #A << ": "; copy(all(A),ostream_iterator<t>(cerr," " )); cerr << endl
#define prp(p) cerr << "(" << (p).first << " ," << (p).second << ")";
#define prArr(A,n,t)  cerr << #A << ": "; copy(A,A + n,ostream_iterator<t>(cerr," " )); cerr << endl
#define pre() cin.tie(0),cerr.tie(0),ios_base::sync_with_stdio(0)
using namespace std;

template <class T>
struct mypair{
	T x,y;
public:
	mypair():x(0),y(0){}
	mypair(T x,T y):x(x),y(y){}
	bool operator < (const mypair<T> & o) const {
		return (x == o.x) ? (y < o.y) : (x < o.x);
	}
	bool operator > (const mypair<T> & o) const {
		return o < *this;
	}
	bool operator != (const mypair<T> & o) const {
		return (*this < o) || (o < *this);
	}
	bool operator == (const mypair<T> & o) const {
		return !(*this != o);
	}
	mypair<T> operator + (const mypair<T> & o){
		return mypair<T>(x + o.x,y + o.y);
	}
	mypair<T> operator * (const ll & n) const {
		return mypair<T>(n*x,n*y);
	}
	mypair<T> operator / (const ll & n) const {
		return mypair<T>(x/n,y/n);
	}
	mypair<T> operator - (const mypair<T> & o) const {
		return *this + (-1LL)*o;
	}
	ll operator * (const mypair<T> & o) const {
		return x*1LL*o.x + y*1LL*o.y;
	}
	ll cross(const mypair<T> & o){
		return x*1LL*o.y - y*1LL*o.x;
	}
	mypair<T> conj(){
		return mypair<T>(x,-y);
	}
	mypair<T> operator / (const mypair<T> & o) const {
		return (*this * o.conj())/hypot(o.x,o.y);
	}
	double angle(){
		double t = atan2(y,x);
		if(t < 0) t += PI;
		return t;	
	}
	friend ostream & operator << (ostream & stream,const mypair<T> & p)  {
		stream << "(" << p.x << " ," << p.y << ")";
		return stream;
	}
	friend istream & operator >> (istream & stream,mypair<T> & p){
		stream >> p.x >> p.y;
		return stream;
	}
	friend void swap(mypair<T> & u,mypair<T> & v){
		using std::swap;		
		u.x ^= v.x ^= u.x ^= v.x;
		u.y ^= v.y ^= u.y ^= v.y;
	}
};

ll L[25],M[25],W[25];
typedef pair<int,pair<int,int> > triple;

unordered_map<ll,unordered_map<ll,pair<ll,vector<triple> > > > F;
vector<triple> RR,LL;
ll tot = LLONG_MIN;

void insert(ll a,ll b,ll c,vector<triple> & C){
	if(F.find(a) == F.end()) F[a] = unordered_map<ll,pair<ll,vector<triple> > >();
	if(F[a].find(b) == F[a].end()) F[a][b] = make_pair(c,C);
	if(F[a][b].xx < c) F[a][b] = make_pair(c,C);
}

void contains(ll a,ll b,ll c,vector<triple> & C){
	if(F.find(a) == F.end()) return ;
	if(F[a].find(b) == F[a].end()) return ;
	if(c + F[a][b].xx >= tot){
		tot = c + F[a][b].xx;
		LL = F[a][b].yy;
		RR = C;
	}
}

void generate(int i,int n,vector<triple> & C,ll *L,ll *M,ll *W,bool cond){
	if(i == n){
		ll a = 0,b = 0,c = 0;
		loop(j,n) {
			auto & p = C[j];
			a += p.xx * L[j];
			b += p.yy.xx * M[j];
			c += p.yy.yy * W[j];		
		}
		if(cond) insert(a-b,b-c,a,C);
		else contains(b-a,c-b,a,C);
		return;	
	} 
	C[i].xx = 1; C[i].yy.xx = 1; C[i].yy.yy = 0;
	generate(i + 1,n,C,L,M,W,cond);
	C[i].xx = 1; C[i].yy.xx = 0; C[i].yy.yy = 1;
	generate(i + 1,n,C,L,M,W,cond);
	C[i].xx = 0; C[i].yy.xx = 1; C[i].yy.yy = 1;
	generate(i + 1,n,C,L,M,W,cond);	
} 

int main(){
	int n;
	scanf("%d",&n);
	loop(i,n) scanf("%I64d %I64d %I64d",L + i,M + i,W + i);
	if(n == 1){
		if(L[0] == M[0] && M[0] == 0) cout << "LM" << endl;
		else if(L[0] == W[0] && W[0] == 0) cout << "LW" << endl;
		else if(M[0] == W[0] && W[0] == 0) cout << "MW" << endl;
		else cout << "Impossible" << endl;
		return 0;
	}	
	vector<triple> C(n/2);
	generate(0,n/2,C,L,M,W,1);
	C.resize(n - (n/2));
	generate(0,n - (n/2),C,L + (n/2),M + (n/2),W + (n/2),0);
	if(LL.empty()) puts("Impossible");
	else{
		for(auto p : LL){
			if(p.xx) putchar('L');
			if(p.yy.xx) putchar('M');
			if(p.yy.yy) putchar('W');
			puts("");
		}
		for(auto p : RR){
			if(p.xx) putchar('L');
			if(p.yy.xx) putchar('M');
			if(p.yy.yy) putchar('W');
			puts("");
		}
	} 
	return 0;
}
