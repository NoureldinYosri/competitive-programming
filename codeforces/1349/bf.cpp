#pragma GCC optimize ("O3")
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
using namespace std;

const int MAX = 1024;
char buffer[MAX];
int m, n, Q;
int G[MAX][MAX];
int dx[] = {0, -1, 0, 1};
int dy[] = {-1, 0, 1, 0};
vector<vector<vi>> TL;


int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	scanf("%d %d %d", &m, &n, &Q);
	loop(i, m){
		scanf("%s", buffer);
		loop(j, n) G[i][j] = buffer[j] - '0';
	}
	vector<vi> g0(m);
	loop(i, m) g0[i] = vi{G[i], G[i] + n};
	TL.emplace_back(g0);
	
	for(int t = 1; t <= 100; t++){
		TL.emplace_back(m);
		auto & g = TL.back();
		loop(i, m) g[i].resize(n, 0);
		loop(i, m) loop(j, n){
			int c = TL[t-1][i][j];
			int f = 0;
			loop(r, 4){
				int x = i + dx[r];
				int y = j + dy[r];
				if(x < 0 || x >= m || y < 0 || y >= n) continue;
				if(TL[t-1][x][y] == c){
					f = 1;
					break;
				}
			}
			
			g[i][j] = c ^ f;
		}
	}
	while(Q--){
		int i, j, t; scanf("%d %d %d", &i, &j, &t);
		cout << TL[t][i-1][j-1] << endl;
	}
	return 0;
}
