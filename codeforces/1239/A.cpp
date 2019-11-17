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


int G[100][100];
int dx[] = {0,-1,0,1};
int dy[] = {-1,0,1,0};

int bf(int n,int m) {
	int N = n*m;
	int ans = 0;
	for (int msk = 0;msk < (1 << N);msk++) {
		for(int i = 0;i < N;i++) {
			int x = i/m;
			int y = i%m;
			G[x][y] = (msk >> i) & 1;
		}
		bool valid = 1;
		loop(x,n) loop(y,m) {
			int ctr = 0;
			loop(r,4) {
				int nx = x + dx[r];
				int ny = y + dy[r];
				if(nx < 0 || ny < 0 || nx >= n || ny >= m) continue;
				ctr += G[x][y] == G[nx][ny];
			}
			valid &= ctr <= 1;
		}
		ans += valid;
	}
	return ans;
}


const int mod = 1000000007,MAX = 2*100*1000 + 10;


int add(int a,int b) {
	a += b;
	if(a >= mod) a -= mod;
	if(a < 0) a += mod;
	return a;
}

vector<int> Fib;

void gen(){
	Fib.push_back(1);
	Fib.push_back(1);
	int u = 1,v = 1;
	for(int i = 1;i <= MAX;i++){
		v = add(u,v);
		Fib.push_back(v);
		swap(v,u);
	}
}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	gen();
	int n,m; cin >> n >> m;
	int ans = add(add(Fib[m],Fib[n]),-Fib[1]);
	ans = add(ans,ans);
	cout << ans << endl;
	return 0;
}
#endif
