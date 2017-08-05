#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define range(i,a,b) for(int i = (a);i <= (b);i++)
#define all(A) A.begin(),A.end()
#define pb push_back
#define mp make_pair
#define sz(A) ((int)A.size())
#define vi vector<int>
#define vl vector<long long>
#define vd vector<double>
#define vp vector<pair<int,int> >
#define ll long long
#define pi pair<int,int>
#define popcnt(x) __builtin_popcount(x)
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

const int MAX = 210;
char grid[MAX][MAX];
int m,n;
int vis[MAX][MAX];
pi S,T;
int dx [] = {0,1,0,-1},dy[] = {-1,0,1,0};
int dist1[MAX][MAX],dist2[MAX][MAX];
vp lev1[MAX*MAX],lev2[MAX*MAX],lev[MAX*MAX];

void bfs(pi S,int dist[MAX][MAX],vp *lev){
	memset(vis,0,sizeof vis);
	memset(dist,-1,sizeof dist);
	deque<pi> q;
	q.push_back(S);
	vis[S.xx][S.yy] = 1;
	dist[S.xx][S.yy] = 0;
	for(int d = 0;!q.empty();d++) {
		int L = q.size();
		while(L--){
			pi cur = q.front();
			q.pop_front();
			loop(i,4){
				int nx = cur.xx + dx[i],ny = cur.yy + dy[i];
				if(nx < 0 || nx >= m || ny < 0 || ny >= n || grid[nx][ny] == 'B' || vis[nx][ny]) continue;
				vis[nx][ny] = 1;
				dist[nx][ny] = dist[cur.xx][cur.yy] + 1;
				q.push_back(mp(nx,ny));
			}
		}
	}
	loop(i,m) loop(j,n) if(dist[i][j] != -1) lev[dist[i][j]].pb(mp(i,j));
}





int get(){
	bfs(T,dist2,lev2);
	int L = dist1[T.xx][T.yy];
	for(int i = 0;i <= L;i++) {
		vp & v1 = lev1[i];
		vp & v2 = lev2[L-i];
		sort(all(v2));
		for(pi x : v1)
			if(binary_search(all(v2),x))
				lev[i].pb(x);
		assert(!lev[i].empty());
	}
	if(L == 1) return -1;
	int m = L/2;
	if((L + 1) & 1) {
		if(sz(lev[m]) == 1) return -1;
		else return L;
	}
	else{
		if(sz(lev[m]) == 1 || sz(lev[m+1]) == 1) return -1;
		else return L;
	}
}

int main(){
	freopen("labyrinth.in", "r", stdin);
	freopen("labyrinth.out", "w", stdout);

	scanf("%d %d",&m,&n);
	loop(i,m) {
		scanf("%s",grid[i]);
		loop(j,n) {
			if(grid[i][j] == 'R') S = mp(i,j);
			if(grid[i][j] == 'S') T = mp(i,j);
		}
	}
	bfs(S,dist1,lev1);
	int c1 = dist1[T.xx][T.yy];
	if(c1 == -1) puts("2");
	else {
		int c2 = get();
//		cerr << c1 << " " << c2 << endl;
		if(c2 == -1 || c1 < c2) puts("1");
		else puts("2");
	}

	return 0;
}
