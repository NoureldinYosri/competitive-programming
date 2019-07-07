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
using namespace std;

const int MAXN = 22;

bool vis[MAXN][MAXN];
vp path;
int R,C;

bool bt(int x,int y) {
	path.push_back(mp(x,y));
	vis[x][y] = 1;
	if(sz(path) == R*C) {
		vis[x][y] = 0;
		return 1;
	}
	loop(i,R) loop(j,C) {
		if(vis[i][j]) continue;
		if(i == x || j == y || i+j == x+y || i-j==x-y) continue;
		if(bt(i,j)) {
			vis[x][y] = 0;
			return 1;
		}
	}
	vis[x][y] = 0;
	path.pop_back();
	return 0;
}

bool bf(int r,int c,bool verbose = 1) {
	assert(path.empty());
	R = r,C = c;
	loop(i,R) loop(j,C) {
		if(bt(i,j)) {
			if(verbose) puts("POSSIBLE");
			if(verbose){
				for(auto p : path)
					printf("%d %d\n",p.xx+1,p.yy+1);
			}
			path.clear();
			return 1;
		}
	}
	if(verbose) puts("IMPOSSIBLE");
	return 0;
}

string toString(pi p) {
	return "(" + to_string(p.xx) + ", " + to_string(p.yy) + ")";
}

vp getNeightbours(int x,int y,bool vis[MAXN][MAXN]){
	vp ret;
	loop(i,R) loop(j,C) {
		if(i == x || j == y || i+j==x+y || i-j==x-y) continue;
		if(vis[i][j]) continue;
		ret.push_back(mp(i,j));
	}
	return ret;
}

vp greedy(){
	static bool vis[MAXN][MAXN];
	static set<pi> G[MAXN][MAXN];
	loop(i,R) loop(j,C) vis[i][j] = 0;
	loop(i,R) loop(j,C) {
		vp aux = getNeightbours(i,j,vis);
		G[i][j].clear();
		for(auto p : aux) G[i][j].insert(p);
	}
	vp path;
	path.push_back(mp(0,0));
	vis[0][0] = 1;
	for(auto p : G[0][0])
		G[p.xx][p.yy].erase(mp(0,0));

	while(1) {
		int x = path.back().xx;
		int y = path.back().yy;
		int best = -1,i = 0,j = 0;
		for(pi p : G[x][y]){
//			vp & aux = G[p.xx][p.yy] = getNeightbours(p.xx,p.yy,vis);
			if(best == -1 || sz(G[p.xx][p.yy]) < best) {
				best = sz(G[p.xx][p.yy]);
				i = p.xx;
				j = p.yy;
			}
		}
		if(best == -1) break;
		path.push_back(mp(i,j));
		vis[i][j] = 1;
		for(auto p : G[i][j])
			G[p.xx][p.yy].erase(mp(i,j));
	}
	return path;
}

int main(int argc,char **argv){
#ifdef HOME
	freopen("in.in","r",stdin);
#endif
	// 2 [2-4]
	// 3,3
	int T; scanf("%d",&T);
	for(int t = 1;t <= T;t++) {
		scanf("%d %d",&R,&C);
		printf("Case #%d: ",t);
		vp path = greedy();
		if(sz(path) == R*C) {
			puts("POSSIBLE");
			for(auto p : path)
				printf("%d %d\n",p.xx+1,p.yy+1);
		}
		else puts("IMPOSSIBLE");
	}

	return 0;
}
