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

struct state{
	int x,y,lst_dir,cnt;
};

const int MAX = 1111;
char G[MAX][MAX];
int m,n;
int dx[] = {-1,0,1,0},dy[] = {0,-1,0,1};
bool vis[MAX][MAX][4][3];
pi S,T;

bool bfs(){
	queue<state> q;
	loop(i,4) {
		q.push(state({S.xx,S.yy,i,2}));
		vis[S.xx][S.yy][i][2] = 1;
	}
	while(!q.empty()){
		state cur = q.front(); q.pop();
		if(T == mp(cur.x,cur.y)) return 1;
		loop(i,4){
			state to = cur;
			to.cnt -= to.lst_dir != i;
			if(to.cnt < 0) continue;
			to.lst_dir = i;
			to.x += dx[i];
			to.y += dy[i];
			if(to.x < 0 || to.y < 0 || to.x >= m || to.y >= n) continue;
			if(G[to.x][to.y] == '*') continue;
			if(vis[to.x][to.y][to.lst_dir][to.cnt]) continue;
			vis[to.x][to.y][to.lst_dir][to.cnt] = 1;
			q.push(to);
		}
	}
	return 0;
}


int main(){
	#ifndef ONLINE_JUDGE
		freopen("input.in", "r", stdin);
		freopen("output.out", "w", stdout);
	#endif
	scanf("%d %d",&m,&n);
	loop(i,m){
		scanf("%s",G[i]);
		loop(j,n) {
			if(G[i][j] == 'S') S = mp(i,j);
			if(G[i][j] == 'T') T = mp(i,j);
		}
	}
	puts(bfs() ? "YES" : "NO");
	return 0;
}
