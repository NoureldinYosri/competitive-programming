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


typedef int card[5][5];

card C[100];
int n;

bool possible(int u,int v) {
	loop(i,5) {
		loop(j,5) {
			int ctr = 0;
			loop(a,5) loop(b,5) if(C[u][i][a] == C[v][j][b]) ctr++;
			if(ctr > 1) return 1;
		}
	}
	return 0;
}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	scanf("%d",&n);
	loop(k,n) {
		loop(i,5) {
			loop(j,5) scanf("%d",&C[k][i][j]);
			sort(C[k][i],C[k][i] + 5);
		}
	}
	pi ans(INT_MAX,-1);
	loop(j,n) loop(i,j) {
		pi cand(i,j);
		if(possible(i,j)) ans = min(ans,cand);
	}
	if(ans.first == INT_MAX) puts("no ties");
	else printf("%d %d\n",ans.first+1,ans.second+1);

	return 0;
}
#endif
