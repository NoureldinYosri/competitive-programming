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


int ask(int x1,int y1,int x2,int y2) {
	x1++,y1++,x2++,y2++;
	cout << "? " << x1 << " " << y1 << " " << x2 << " " << y2 << endl;
	int res; cin >> res;
	if(res==-1) exit(0);
	return res;
}

const int MAX = 55;
int G[MAX][MAX],O[2][MAX][MAX];
int n;

void output(int G[MAX][MAX]){
	puts("!");
	loop(i,n) {
		loop(j,n) {
			char c = '$';
			if(G[i][j] != -1) c = G[i][j] + '0';
			putchar(c);
		}
		puts("");
	}
}

void query() {
	G[0][0] = 1;
	G[n-1][n-1] = 0;

	G[1][1] = ask(0,0,1,1);

	G[0][1] = 1;
	G[1][2] = ask(0,1,1,2);
	G[1][0] = ask(1,0,1,2) ? G[1][2] : (1-G[1][2]);

	for(int c = 0;c < 2;c++)
		for(int r = 2;r < n;r++) {
			G[r][c] = ask(r-2,c,r,c) ? G[r-2][c] : (1-G[r-2][c]);
		}
	for(int r = 0;r < n;r++)
		for(int c = 2;c < n;c++) {
			if(G[r][c] != -1) continue;
			G[r][c] = ask(r,c-2,r,c) ? G[r][c-2] : (1 - G[r][c-2]);
		}
}

int fL(int x,int y,int G[MAX][MAX]) {
	return (G[x][y]==G[x+1][y+2]) &&
			(G[x][y+1]==G[x][y+2] || G[x][y+1]==G[x+1][y+1] || G[x+1][y]==G[x+1][y+1]);
}


int fR(int x,int y,int G[MAX][MAX]) {
	return (G[x][y]==G[x+2][y+1]) &&
			(G[x+1][y]==G[x+2][y] || G[x+1][y]==G[x+1][y+1] || G[x][y+1]==G[x+1][y+1]);
}

vp ST;

bool cond(int G[MAX][MAX]) {
	int m = sz(ST);
	for(int i = 0;2*i < m;i++) {
		pi l = ST[i],r = ST[m-1-i];
		int a = G[l.first][l.second];
		int b = G[r.first][r.second];
		if(a != b) return 0;
	}
	return 1;
}

bool bt(int x,int y,int tx,int ty,int G[MAX][MAX]) {
	if(x > tx || y > ty) return 0;
	ST.emplace_back(x,y);
	if(x == tx && y == ty) {
		bool res = cond(G);
		ST.pop_back();
		return res;
	}
	bool res = bt(x+1,y,tx,ty,G) || bt(x,y+1,tx,ty,G);
	ST.pop_back();
	return res;
}

int f3(int x,int y,int G[MAX][MAX]) {
	ST.clear();
	return bt(x,y,x+2,y+2,G);
}

int main(){
	cin >> n;
	memset(G,-1,sizeof G);
	query();
//	cerr << "cand are " << endl;
	loop(v,2) {
		loop(i,n) loop(j,n) {
			O[v][i][j] = G[i][j];
			if((i+j)%2) O[v][i][j] ^= v;
		}
//		cerr << endl;
//		loop(i,n) {
//			prArr(O[v][i],n,int);
//		}
//		cerr << string(10,'*') << endl;
	}
	bool found = 0;
	loop(i,n-1) loop(j,n-2) {
		int a = fL(i,j,O[0]),b = fL(i,j,O[1]);
		if(a != b){
			int truth = ask(i,j,i+1,j+2);
			output(O[b==truth]);
			exit(0);
		}
	}
	assert(0);
	return 0;
}
#endif
