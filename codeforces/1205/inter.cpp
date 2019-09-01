#ifdef DEBUG
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

const int MAX = 55;
string grid[MAX] = {"100","001","000"};
int n = 3;

void output_case(){
	cerr << n << endl;
	loop(j,n) cerr << grid[j] << endl;
}

short dp[MAX][MAX][MAX][MAX];

int solve(int x1,int y1,int x2,int y2) {
	if(x1 > x2 || y1 > y2) return 0;
//	cerr << x1 << " " << y1 << " " << x2 << " " << y2 << endl;
	if(x2+y2-x1-y1 <= 1) return grid[x1][y1] == grid[x2][y2];
	short & res = dp[x1][y1][x2][y2];
	if(res != -1) return res;
	res = 0;
	loop(i,2) loop(j,2) {
		res |= solve(x1+(i%2),y1+1-(i%2),x2-(j%2),y2-1+(j%2));
	}
	res &= grid[x1][y1] == grid[x2][y2];
	return res;
}

void work(){
	memset(dp,-1,sizeof dp);
	cout << n << endl;
	int ctr = 0;
	while(1){
		char c; cin >> c;
		cerr << "c is " << c << endl;
		if(c == '!') {
			cerr << "reading res" << endl;
			vector<string> res(n);
			loop(i,n) {
				cin >> res[i];
				cerr << res[i] << endl;
			}
			loop(i,n){
				if(res[i] != grid[i]) {
					cerr << "row " << i+1 << "miss match" << endl;
					cerr << "expected:" << endl;
					output_case();
					cerr << "found:" << endl;
					loop(j,n) cerr << res[j] << endl;
					exit(1);
				}
			}
			cerr << "correct :)" << endl;
 			exit(0);
		}
		ctr++;
		if(ctr > n*n) {
			cerr << "#queries exceeded limit" << endl;
			output_case();
			exit(1);
		}
		int x1,y1,x2,y2;
		cin >> x1 >> y1 >> x2 >> y2;
//		cerr << "read " << x1 << " " << y1 << " " << x2 << " " << y2 << endl;
		bool valid = 1;
		valid &= 1 <= x1 && x1 <= x2 && x2 <= n;
		valid &= 1 <= y1 && y1 <= y2 && y2 <= n;
		valid &= x2+y2-x1-y1 >= 2;
		if(!valid) {
			cout << -1 << endl;
			cerr << "invalid query" << endl;
			output_case();
			exit(1);
		}
		x1--,y1--,x2--,y2--;
		int res = solve(x1,y1,x2,y2);
//		cerr << "returning " << res << endl;
		cout << res << endl;
	}
}

int main(int argc,char **argv){
	if(argc > 1) {
		sscanf(argv[1],"%d",&n);
		loop(i,n) grid[i] = string(argv[2+i]);
	}
	work();
	cerr << "no grid recieved" << endl;
	return 0;
}
#endif
