#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define range(i,a,b) for(int i = (a);i <= (b);i++)
#define rrep(i,n) for(int i = (n);i >= 0;i--)
#define rran(i,a,b) for(int i = (b);i >= (a);i--)
#define step(i,a,b,d) for(int i = (a);i <= (b); i += d)
#define all(A) A.begin(),A.end()
#define PI acos(-1)
#define pb push_back
#define mp make_pair
#define sz(A) A.size()
#define len(A) A.length()
#define vi vector<int>
#define ll long long
#define pi pair<int,int>
#define point pair<double,double>
#define pl pair<ll,ll>
#define popcnt(x) __builtin_popcount(x)
#define LSOne(x) ((x) & (-(x)))
#define xx first
#define yy second
#define PQ priority_queue
#define print(A,t) cerr << #A << ": "; copy(all(A),ostream_iterator<t>(cerr," " )); cerr << endl
#define prp(p) cerr << "(" << (p).first << " ," << (p).second << ")";
#define prArr(A,n,t)  cerr << #A << ": "; copy(A,A + n,ostream_iterator<t>(cerr," " )); cerr << endl
#define pre() cin.tie(0),cerr.tie(0),ios_base::sync_with_stdio(0)
using namespace std;

struct node{
	int x,y,z;
public:
	node(){}
	node(int a,int b,int c):x(a),y(b),z(c){}
	bool operator != (const node & o){
		return x != o.x || y != o.y || z != o.z;
	}
};

int D[11][11],dx[] = {-1,1,0,0},dy[] = {0,0,-1,1};
char G[20][20][22];
int V[20][20][20],N,X,Y,C,T;
node P[11];
int ord[11];

void bfs(int s){
	deque<node> q;
	q.push_back(P[s]);
	loop(i,N) loop(j,X) loop(k,Y) V[i][j][k] = -1;
	V[P[s].z][P[s].x][P[s].y] = 0;
	while(!q.empty()){
		int x = q.front().x,y = q.front().y,z = q.front().z; q.pop_front();
		if('0' <= G[z][x][y] && G[z][x][y] <= '9') {
			D[s][G[z][x][y] - '0'] = V[z][x][y]; 
		//	cerr << s << " " << G[z][x][y] << " " << V[z][x][y] << endl;
		}
		if(x == 0 && y == 0 && z == 0) D[s][10] = V[z][x][y]; 
		loop(i,4){
			int nx = x + dx[i],ny = y + dy[i];
			if(nx < 0 || nx == X || ny < 0 || ny == Y) continue;
			if(G[z][nx][ny] == '*') continue;
			if(V[z][nx][ny] != -1) continue;
			V[z][nx][ny] = V[z][x][y] + 1;
			q.push_back(node(nx,ny,z));
		}
		if('a' <= G[z][x][y] && G[z][x][y] <= 'z'){
			int nz = G[z][x][y] - 'a';
			if(G[nz][x][y] == '*') continue;
			if(V[nz][x][y] != -1) continue;
			V[nz][x][y] = V[z][x][y];
			q.push_front(node(x,y,nz));
		//	cerr << "from " <<z << " "<<  x << " " << y << " -> " << nz << " " << x << " " << y << endl;
		}
	}
}

int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%d %d %d %d",&N,&X,&Y,&C);
		int ctr = 1;
		loop(i,11) loop(j,11) D[i][j] = 1 << 20;
		loop(i,N) loop(j,X) {
			scanf("%s",G[i][j]);
			loop(k,Y) {
				if(G[i][j][k] == '!') P[0] = node(j,k,i),G[i][j][k] = '0';
				else if(G[i][j][k] == 'S') {
					P[ctr] = node(j,k,i);
					G[i][j][k] = ctr + '0';
					++ctr;
				}
			}
		}
		loop(i,ctr) bfs(i); bfs(10);
		int k = ctr - 1,ans = INT_MAX;	
		//cerr << k << endl;	
		loop(mask,1 << k){
			if(popcnt(mask) == C){
				ord[0] = 0; int z = 1;
				ord[C + 1] = C + 1;
				loop(i,k) if(mask & (1 << i)) ord[z++] = i + 1;
				do{
					int tmp = 0;
					loop(i,C) {
						tmp += D[ord[i]][ord[i + 1]];
				//		cerr << ord[i] << " " << ord[i + 1] << " " << D[ord[i]][ord[i + 1]] << endl;
					}
					tmp += D[ord[C]][10];
				//	cerr << ord[C] << " " << 10 << " " << D[ord[C]][10] << endl;						
				//	cerr << endl;
					ans = min(ans,tmp);
				}while(next_permutation(ord + 1,ord + z));
			}
		}
		if(ans >= (1 << 20)) ans = -1;
		printf("%d\n",ans);
	}
	return 0;
}
