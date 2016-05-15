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

char G[1000][1000];
int m,n;

int F[1000][1000][2];
int Q[1000][1000];

inline int IsEmpty(int x,int y){
	if(x < 0 || x == m) return 0;
	if(y < 0 || y == n) return 0;
	return G[x][y] == '.';
}

int main(){
	scanf("%d %d",&m,&n);
	loop(i,m) scanf("%s",G[i]);
	loop(i,m) loop(j,n){
		F[i][j][0] = IsEmpty(i - 1,j) * IsEmpty(i,j);
		F[i][j][1] = IsEmpty(i,j - 1) * IsEmpty(i,j);
		Q[i][j] = F[i][j][0] + F[i][j][1];
		
		if(i) Q[i][j] += Q[i - 1][j];
		if(j) Q[i][j] += Q[i][j - 1];
		if(i && j) Q[i][j] -= Q[i - 1][j - 1];
		
		if(j) F[i][j][0] += F[i][j - 1][0];
		if(i) F[i][j][1] += F[i - 1][j][1]; 	
	}
	/*loop(i,m) {
		prArr(Q[i],n,int);
	}*/
	int q,a,b,c,d;
	scanf("%d",&q);
	while(q--){
		scanf("%d %d %d %d",&a,&b,&c,&d);
		a--,b--,c--,d--;
		int ans = Q[c][d];
		if(a) ans -= Q[a - 1][d];
		if(b) ans -= Q[c][b - 1];
		if(a && b) ans += Q[a - 1][b - 1];
		
		if(a) {
			ans -= F[a][d][0];
			if(b) ans += F[a][b - 1][0];
		}
		if(b) {
			ans -= F[c][b][1];
			if(a) ans += F[a - 1][b][1];
		}
		printf("%d\n",ans);
	}	
	return 0;
}
