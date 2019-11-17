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


int n,m,K;
map<int,set<int> > rows;
map<int,set<int> > cols;

int dx [] = {0,1,0,-1};
int dy[] = {1,0,-1,0};



pi moveRight(int x,int y,int l,int r) {
	if(!rows.count(x)) return pi(x,r);
	auto & M = rows[x];
	auto ptr = M.upper_bound(y);
	if(ptr == M.end()) return pi(x,r);
	y = (*ptr) - 1;
	y = min(y,r);
	return pi(x,y);
}

pi moveLeft(int x,int y,int l,int r) {
	if(!rows.count(x)) return pi(x,l);
	auto & M = rows[x];
	auto ptr = M.lower_bound(y);
	if(ptr == M.begin()) return pi(x,l);
	ptr--;
	y = (*ptr) + 1;
	y = max(y,l);
	return pi(x,y);
}
pi moveDown(int x,int y,int l,int r) {
	if(!cols.count(y)) return pi(r,y);
	auto & M = cols[y];
	auto ptr = M.upper_bound(x);
	if(ptr == M.end()) return pi(r,y);
	x = (*ptr) - 1;
	x = min(x,r);
	return pi(x,y);
}
pi moveUp(int x,int y,int l,int r) {
	if(!cols.count(y)) return pi(l,y);
	auto & M = cols[y];
	auto ptr = M.lower_bound(x);
	if(ptr == M.begin()) return pi(l,y);
	ptr--;
	x = (*ptr) + 1;
	x = max(x,l);
	return pi(x,y);
}


char D[] = "RDLU";


bool solve(){
	int x = 1,y = 1,dir = 0;
	int s_row = 1,e_row = n;
	int s_col = 1,e_col = m;
	ll cnt = 1;
	pi nxt;
	if(m == 1 || moveRight(1,1,1,m).second == 1) dir = 1;
	while(s_row <= e_row && s_col <= e_col) {
//			cout << x << " " << y << " " << D[dir] << " " << turns << " "
//					<< "rows " << s_row << " " << e_row << " cols " << s_col << " " << e_col << endl;
		if(dir == 0) {
			nxt = moveRight(x,y,s_col,e_col);
			s_row = x+1;
		}
		else if(dir == 1) {
			nxt = moveDown(x,y,s_row,e_row);
			e_col = y-1;
		}
		else if(dir == 2) {
			nxt = moveLeft(x,y,s_col,e_col);
			e_row = x-1;
		}
		else {
			nxt = moveUp(x,y,s_row,e_row);
			s_col = y+1;
		}
		if(nxt == pi(x,y)) break;
		cnt += abs(nxt.first - x) + abs(nxt.second - y);
		x = nxt.first;
		y = nxt.second;
		dir = (dir+1)%4;
	}
	return cnt == n*(ll)m - K;
}

char G[1000][1000];

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	scanf("%d %d %d",&n,&m,&K);
#ifdef HOME
	loop(i,n) loop(j,m) G[i+1][j+1] = '0';
#endif
	loop(i,K){
		int r,c; scanf("%d %d",&r,&c);
		rows[r].insert(c);
		cols[c].insert(r);
#ifdef HOME
		G[r][c] = '1';
#endif
	}
#ifdef HOME
	loop(i,n) puts(G[i+1]+1);
#endif
	puts(solve() ? "yes" : "no");
	return 0;
}
