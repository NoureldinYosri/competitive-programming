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


int main(){
	ll x,y; 
	cin >> x >> y;
	if(__gcd(x,y) != 1) cout << "Impossible" << endl;
	else{
		while(y && x){
			if(x > y) {
				cout << x/y - (y == 1) << "A";
				x %= y;
			}
			else {
				cout << y/x - (x == 1) << "B";
				y %= x;
			}
		}
		cout << endl;
	}		
	return 0;
}
