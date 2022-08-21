#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define all(A) A.begin(),A.end()
#define pb push_back
#define mp make_pair
#define sz(A) ((int)A.size())
using vi = std::vector<int>;
using pi = std::pair<int,int>;
using vp = std::vector<pi>;
using ll = long long;
#define popcnt(x) __builtin_popcount(x)
#define LSOne(x) ((x) & (-(x)))
#define print(A,t) cerr << #A << ": "; copy(all(A),ostream_iterator<t>(cerr," " )); cerr << endl
#define prArr(A,n,t)  cerr << #A << ": "; copy(A,A + n,ostream_iterator<t>(cerr," " )); cerr << endl
#define PRESTDIO() cin.tie(0),cerr.tie(0),ios_base::sync_with_stdio(0)
#define what_is(x) cerr << #x << " is " << x << endl
#define bit_lg(x) (assert(x > 0),__builtin_ffsll(x) - 1)
template<class A,class B>
std::ostream& operator << (std::ostream& st,const std::pair<A,B> p) {
	st << "(" << p.first << ", " << p.second << ")";
	return st;
}
void tc();
auto test_cases = [](){
	int T; scanf("%d", &T);
	while(T--) tc();
};
using namespace std;

const int MAX = 512;
char G[MAX][MAX];
int m, n;
const vi dx {-1, 0, 1, 0, 1, 1};
const vi dy {0, 1, 0, -1, 1, -1};


void tc() {
	scanf("%d %d", &m, &n);
	loop(i, m) scanf("%s", G[i]);
	int cnt = 0;
	loop(i, m) loop(j, n) cnt += G[i][j] == '1';
	if(cnt == 0) {
		puts("0");
		return;
	}
	if(cnt == m*n) {
		printf("%d\n", cnt - 2);
		return;
	}
	loop(i, m) loop(j, n) if(G[i][j] == '0') {
		bool found = false;
		loop(r, sz(dx)) {
			int x = i + dx[r];
			int y = j + dy[r];
			if(x >= 0 && y >= 0 && x < m && y < n && G[x][y] == '0') {
				found = true;
				break;
			}
		}
		if(found) {
			printf("%d\n", cnt);
			return;
		}
	}
	printf("%d\n", cnt - 1);
}


int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	test_cases();
	return 0;
}
