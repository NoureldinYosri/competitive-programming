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

const int MAXN = 511,MAX = MAXN*MAXN;
int H[MAXN][MAXN];
int name[MAXN][MAXN];
int id[MAX],W[MAX];
int m,n,Q;
map<int,int> E[MAX];
int dx[] = {-1,0,1,0},dy[] = {0,1,0,-1};

int find(int a) {
	while(a != id[a]) a = id[a];
	return a;
}
void join(int a,int b,int h) {
	a = find(a);
	b = find(b);
	if(a == b) return;
	if(W[a] < W[b]) swap(a,b);
	W[a] += W[b];
	id[b] = a;
	E[a][b] = h;
}

void init(){
	vector<pi> ord;
	loop(i,m) loop(j,n) {
		name[i][j] = i*n + j;
		W[name[i][j]] = 1;
		id[name[i][j]] = name[i][j];
		ord.push_back(pi(i,j));
	}
	sort(all(ord),[](const pi & a,const pi & b) {
		return H[a.first][a.second] < H[b.first][b.second];
	});
	for(auto p : ord) {
		for(int r = 0;r < 4;r++) {
			int x = p.first + dx[r];
			int y = p.second + dy[r];
			if(x < 0 || x >= m || y < 0 || y >= n) continue;
			if(H[x][y] > H[p.first][p.second]) continue;
			join(name[x][y],name[p.first][p.second],H[p.first][p.second]);
		}
	}
}

int solve(int a,int b) {
	int h = max(H[a/n][a%n],H[b/n][b%n]);
	while(a != b) {
		if(W[a] < W[b]) swap(a,b);
		int p = id[b];
		assert(E[p].count(b));
		h = max(h,E[p][b]);
		b = p;
	}
	return h;
}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	scanf("%d %d %d",&m,&n,&Q);
	loop(i,m) loop(j,n) scanf("%d",&H[i][j]);
	init();
	while(Q--) {
		int x1,y1,x2,y2;
		scanf("%d %d %d %d",&x1,&y1,&x2,&y2);
		x1--,y1--,x2--,y2--;
		printf("%d\n",solve(name[x1][y1],name[x2][y2]));
	}
	return 0;
}
#endif
