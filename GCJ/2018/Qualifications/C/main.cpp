#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define range(i,a,b) for(int i = (a);i <= (b);i++)
#define all(A) A.begin(),A.end()
#define pb push_back
#define mp make_pair
#define sz(A) ((int)A.size())
#define vi vector<int>
#define vd vector<double>
#define vp vector<pair<int,int> >
#define ll long long
#define pi pair<int,int>
#define popcnt(x) __builtin_popcountll(x)
#define LSOne(x) ((x) & (-(x)))
#define xx first
#define yy second
#define PQ priority_queue
#define print(A,t) cerr << #A << ": "; copy(all(A),ostream_iterator<t>(cerr," " )); cerr << endl
#define prp(p) cerr << "(" << (p).first << " ," << (p).second << ")";
#define prArr(A,n,t)  cerr << #A << ": "; copy(A,A + n,ostream_iterator<t>(cerr," " )); cerr << endl
#define PRESTDIO() cin.tie(0),cerr.tie(0),ios_base::sync_with_stdio(0)
#define what_is(x) cerr << #x << " is " << x << endl
#define bit_lg(x) (assert(x > 0),__builtin_ffsll(x) - 1)
const double PI = acos(-1);
using namespace std;

const int MAX = 1024;
int A;
int done[MAX][MAX];
int cnt[MAX][MAX];

void solve(){
	int n = 3;
	while(n*n < A) n++;

	set<pair<int,pi>> E;
	for(int i = 1;i <= n;i++)
		for(int j = 1;j <= n;j++)
			cnt[i][j] = 0;

	for(int i = 2;i < n;i++)
		for(int j = 2;j < n;j++){
			cnt[i][j] = 9;
			E.insert(mp(9,mp(i,j)));
		}

	for(int i = 1;i <= n;i++)
		for(int j = 1;j <= n;j++)
			done[i][j] = 0;

	while(1) {
		pair<int,pi> t = *E.rbegin();
		pi c = t.yy;
		printf("%d %d\n",c.xx,c.yy);
		fflush(stdout);

		int x,y; scanf("%d %d",&x,&y);
		if(x== 0 && y==0) break;
		if(x==-1 && y==-1) assert(0);
		if(!done[x][y]) {
			done[x][y] = 1;
			for(int dx = -1;dx <= 1;dx++)
				for(int dy = -1;dy <= 1;dy++) {
					int a = x + dx,b = y + dy;
					if(a <= 1 || a >= n || b <= 1 || b >= n) continue;
					if(!cnt[a][b]) continue;
					E.erase(mp(cnt[a][b],mp(a,b)));
					cnt[a][b]--;
					E.insert(mp(cnt[a][b],mp(a,b)));
				}

		}
	}
}

int main(int argc,char **argv){
#ifdef HOME
	freopen("in.in","r",stdin);
#endif

	int T; scanf("%d",&T);
	for(int t = 1;t <= T;t++) {
		scanf("%d",&A);
		solve();
	}


	return 0;
}
