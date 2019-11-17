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

const int MAX = 111;
char res[MAX][MAX];
int cnt[MAX][MAX];
int m,n;

int getCount(int r,int c) {
	int ret = 0;
	for(int dx = -1;dx <= 1;dx++)
		for(int dy = -1;dy <= 1;dy++) {
			int x = r + dx,y = c + dy;
			if(x < 0 || x >= m+2 || y < 0 || y >= n+2) continue;
			ret += res[x][y] == 'X';
		}
	return ret;
}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	scanf("%d %d",&m,&n);
	loop(i,m+2) loop(j,n+2) {
		scanf("%d",&cnt[i][j]);
		res[i][j] = '.';
	}
	for(int r = 1;r <= m;r++)
		for(int c = 1;c <= n;c++) {
			int ctr = getCount(r-1,c-1);
			int diff = cnt[r-1][c-1] - ctr;
//			cerr << r-1 << " " << c-1 << ": " << ctr << " " << cnt[r-1][c-1] << endl;
			if(diff == 0) continue;
			if(diff == 1) {
//				cerr << r << " " << c << " is black" << endl;
				res[r][c] = 'X';
				continue;
			}
			puts("impossible");
			return 0;
		}
	loop(r,m+2) loop(c,n+2) if(getCount(r,c) != cnt[r][c]) {
		puts("impossible");
		return 0;
	}
	for(int r = 1;r <= m;r++){
		res[r][n+1] = 0;
		puts(res[r]+1);
	}
	return 0;
}
#endif
