#ifdef ACTIVE
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

const int mod = 1000000007;
const int MAX = 1 << 10;
int G[MAX][MAX];

int R[MAX],C[MAX];
int H,W;

int color[MAX][MAX];

bool valid(){
	loop(r,H) loop(c,W) color[r][c] = 2;
	loop(r,H) {
		loop(i,R[r]) color[r][i] = 1;
		color[r][R[r]] = 0;
	}
	loop(c,W){
		loop(i,C[c]) color[i][c] = 1;
		color[C[c]][c] = 0;
	}
	loop(r,H) {
		int c = 0;
		while(c < W && color[r][c]==1) c++;
		if(c != R[r]) return 0;
	}
	loop(c,W) {
		int r = 0;
		while(r < H && color[r][c]==1) r++;
		if(r != C[c]) return 0;
	}
	return 1;
}

int powmod(ll x,int p){
	if(p == 0) return 1;
	ll y = 1;
	for(;p > 1;p >>= 1) {
		if(p&1) y = (x*(ll)y)%mod;
		x = (x*(ll)x)%mod;
	}
	return (x*y)%mod;
}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	scanf("%d %d",&H,&W);
	loop(i,H) scanf("%d",R + i);
	loop(i,W) scanf("%d",C + i);
	if(!valid()) {
		puts("0");
		return 0;
	}

	int free_cells = 0;
	loop(r,H) loop(c,W) {
		free_cells += color[r][c] == 2;
	}
//	cout << free_cells << endl;
	printf("%d\n",powmod(2,free_cells));
	return 0;
}
#endif
