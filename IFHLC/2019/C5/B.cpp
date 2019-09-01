#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define all(A) A.begin(),A.end()
#define pb push_back
#define mp make_pair
#define sz(A) ((int)A.size())
typedef std::vector<int> vi;
typedef std::pair<int,int> pi;
typedef std::vector<pi> vp;
typedef long long ll;
#define popcnt(x) __builtin_popcount(x)
#define LSOne(x) ((x) & (-(x)))
#define print(A,t) cerr << #A << ": "; copy(all(A),ostream_iterator<t>(cerr," " )); cerr << endl
#define prArr(A,n,t)  cerr << #A << ": "; copy(A,A + n,ostream_iterator<t>(cerr," " )); cerr << endl
#define PRESTDIO() cin.tie(0),cerr.tie(0),ios_base::sync_with_stdio(0)
#define what_is(x) cerr << #x << " is " << x << endl
#define bit_lg(x) (assert(x > 0),__builtin_ffsll(x) - 1)
const double PI = acos(-1);
template<class A,class B>
std::ostream& operator << (std::ostream& st,const std::pair<A,B> p) {
	st << "(" << p.first << ", " << p.second << ")";
	return st;
}
#define tc() int T; scanf("%d",&T); for(int t = 1;t <= T;t++)
using namespace std;

bool inRectangle(ll x,ll y,ll h,ll w) {
//	cerr << "checking " << x << " " << y << " vs " << w << " " << h << endl;
	return x < w && y < h && x >= 0 && y >= 0;
}

bool inLShape(ll x,ll y,ll len) {
	return inRectangle(x,y,len,len/2) || inRectangle(x,y,len/2,len);
}

ll getLen(ll x,ll y) {
	ll len = 2;
	while(!inLShape(x,y,len))
		len <<= 1;
	return len;
}

void rotate90(ll & x,ll & y,ll len,bool check = 1) {
//	cerr << "in " << x << " " << y << " " << len << endl;
	ll t = -y;
	y = x;
	x = t;
	x = len-1 + x;
//	cerr << "out " << x << " " << y << " " << len << endl;
	if(check) assert(inLShape(x,y,len));
}

void rotate180(ll & x,ll & y,ll len) {
//	cerr << "in " << x << " " << y << " " << len << endl;
	ll t = y;
	y = -x;
	x = t;
	y = len-1 + y;
//	cerr << "out " << x << " " << y << " " << len << endl;
	assert(inLShape(x,y,len));
}

bool in180LShape(ll x,ll y,ll len) {
	return inRectangle(x,y,len,len/2) || inRectangle(x-len/2,y,len/2,len);
}

int solve(ll x,ll y,ll len){
//	cerr << x << " " << y << " " << len << endl;
//	cerr << "asserting " << x << " " << y << " " << len << endl;
	assert(inLShape(x,y,len));
	if(len == 2) return 0;
	int res = 0,c = -1;
	if(inLShape(x,y,len/2)) {
//		cerr << "c0" << endl;
//		cerr << x << " " << y << endl;
		res = solve(x,y,len/2);
		c = 0;
	}
	else if(inLShape(x-len/4,y-len/4,len/2)) {
//		cerr << "c1" << endl;
		res = solve(x-len/4,y - len/4,len/2);
		c = 1;
	}
	else if(x >= len/2) {
		c = 2;
		if(len == 4) res = 3;
		else {
			ll nx = x - len/2,ny = y;
			rotate180(nx,ny,len/2);
//			cerr << "new " << nx << " " << ny << " " << len/4 << endl;
//			cerr << "2 " << nx << " " << ny << endl;
			res = solve(nx,ny,len/2);
			res += 3;
		}
	}
	else {
		c = 3;
		if(len == 4) res = 1;
		else {
			ll nx = x,ny = y - len/2;
			rotate90(nx,ny,len/2);
//			cerr << nx << " " << ny << " " << len/4 << endl;
//			cerr << "3 new is " << nx << " " << ny << endl;
			res = solve(nx,ny,len/2);
			res++;
		}
	}
	res = (res%4 + 4)%4;
//	cerr << len << " " << c << " " << res << endl;
	return res;
}


int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	tc(){
		ll x,y; scanf("%lld %lld",&x,&y);
		ll len = getLen(x,y);
//		cerr << len << endl;
		printf("%d\n",solve(x,y,len));
	}
	return 0;
}
