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

const int MAXN = 1024,MAXP = 10;
char G[MAXN][MAXN];
int m,n,p;
int ID[MAXN][MAXN],dist[MAXN][MAXN];
int S[MAXP];
int dx[] = {-1,0,1,0},dy[] = {0,1,0,-1};

struct cell{
	int r,c;
};

bool inRange(int x,int s,int e) {
	return s <= x && x <= e;
}

bool valid(int x,int y) {
	return inRange(x,0,m-1) && inRange(y,0,n-1) && G[x][y] != '#' && ID[x][y] == -1;
}

void bfs(cell root,queue<cell> & Q) {
	static queue<cell> q;
	int id = ID[root.r][root.c],s = S[id];
	q.push(root);
	dist[root.r][root.c] = 0;
	while(!q.empty()) {
		cell cur = q.front();
		q.pop();
//		fprintf(stderr,"%d %d: %d %d\n",root.r,root.c,cur.r,cur.c);
		if(dist[cur.r][cur.c] == s) {
			Q.push(cur);
			continue;
		}
		loop(i,4) {
			int r = cur.r + dx[i];
			int c = cur.c + dy[i];
			if(valid(r,c)) {
				ID[r][c] = id;
				dist[r][c] = dist[cur.r][cur.c] + 1;
				q.push(cell({r,c}));
			}
		}
	}
}

void bfs(){
	queue<cell> q[2];
	int u = 0;
	vector<cell> V;
	loop(r,m) loop(c,n) {
		ID[r][c] = -1;
		if(inRange(G[r][c],'1','9')) {
			ID[r][c] = G[r][c] - '1';
			V.pb(cell({r,c}));
		}
	}
	sort(all(V),[](const cell & a,const cell & b) {
		return G[a.r][a.c] < G[b.r][b.c];
	});
	for(cell c : V) q[u].push(c);
	while(!q[u].empty()) {
		while(!q[u].empty()) {
			bfs(q[u].front(),q[u^1]);
			q[u].pop();
		}
		u ^= 1;
	}
}

int main(int argc,char **argv){
#ifdef HOME
	freopen("in.in","r",stdin);
#endif
	scanf("%d %d %d",&m,&n,&p);
	loop(i,p) scanf("%d",S + i);
	loop(r,m) scanf("%s",G[r]);
	bfs();
	int ctr[MAXP] = {0};
	loop(r,m) loop(c,n) if(ID[r][c] != -1) ctr[ID[r][c]]++;
	loop(r,m) {
		prArr(ID[r],n,int);
	}
	loop(i,p) printf("%d%c",ctr[i]," \n"[i==p-1]);
	return 0;
}
