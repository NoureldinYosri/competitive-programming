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


string ans[3];


int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	int W,a,b; scanf("%d %d %d",&W,&a,&b);
	loop(i,3) ans[i] = string(W,'.');
	a--,b--;
	ans[0][a] = 'A';
	ans[1][0] = 'X';
	ans[2][b] = 'B';
	if(a == b) {
		puts("Possible");
		loop(i,3) puts(ans[i].c_str());
		return 0;
	}
	if((a+b)&1) {
		puts("Impossible");
		return 0;
	}
	if(min(a,b) == 0){
		puts("Impossible");
		return 0;
	}
	int x = (a + b - 2)/2;
	int r = (a < b) ? 0 : 2;
	ans[r][min(a,b)-1] = '*';
	for(int c = min(a,b);c < x;c++)
		ans[1][c] = '*';
	if(min(a,b) == x)
		ans[1][x-1] = '*';
	if(ans[1][0] != 'X') {
		puts("Impossible");
		return 0;
	}
	puts("Possible");
	loop(i,3) puts(ans[i].c_str());
	return 0;
}
#endif
