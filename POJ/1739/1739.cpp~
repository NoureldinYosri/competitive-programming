#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <algorithm>
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


int V[10][10],m,n; int ans;
int degree[10][10],dx [] = {-1,1,0,0},dy [] = {0,0,-1,1};
char G[20][20];
int col[20],row[20];

inline void mark(int i,int j){
	V[i][j] = 1;	
	loop(k,4){
		int nx = i + dx[k],ny = j + dy[k];
		degree[nx][ny] --;	 
	}
	row[i]++;
	col[j]++;
}

inline void unmark(int i,int j){
	V[i][j] = 0;	
	loop(k,4){
		int nx = i + dx[k],ny = j + dy[k];
		degree[nx][ny] ++;
	}
	row[i]--;
	col[j]--;
}

bool deadend(int i,int j,int & ox,int & oy,int & ready){
	int aretwos = 0,deadends = 0; ready = 0;
	int can[4];
	loop(k,4){
		can[k] = 0;
		int nx = i + dx[k],ny = j + dy[k];
		if(nx == 0 || nx == m + 1 || ny == 0 || ny == n + 1) continue;
		if(degree[nx][ny] == 1 && (nx == m && ny == n)) ready = 1;
		if(degree[nx][ny] == 1 && !(nx == m && ny == n) && !V[nx][ny]) return 1;
		if(degree[nx][ny] == 2 && !(nx == m && ny == n) && !V[nx][ny]) {
			aretwos ++;
			ox = nx;
			oy = ny;
		}
		deadends += degree[nx][ny] <= 1 && nx >= 1 && nx <= m && ny >= 1 && ny <= n;
		can[k] = !V[nx][ny];
	}
	if(aretwos > 1) return 1;
	if(degree[i][j] == 2 && ((can[0] && can[1]) || (can[2] && can[3]))) return 1;
	if(j != n && col[j + 1] == m) return 1;
	if(i != m && row[i + 1] == n) return 1; 
	if(i == m && !V[m][j-1]) return 1;
	if(j == n && !V[i-1][n]) return 1;
	if(i == 1 && !V[1][j-1]) return 1;
	if(j == 1 && !V[i+1][1]) return 1;
	//if(deadends > 1) return 1;
	return 0;
}


void bt(int i,int j,int ctr){
	if(ctr == 1) {ans += (i == m) && (j == n) ; return;}
	if(i == m && j == n) return;
	int ox = -1,oy = -1,ready;	
	if(deadend(i,j,ox,oy,ready)) return;	
	ctr--;	
	mark(i,j);		
	if(ready){
		bt(m,n,ctr);
		return unmark(i,j);
	}
	if(ox != -1){
		bt(ox,oy,ctr);
		return unmark(i,j);
	}
	loop(k,4){
		int nx = i + dx[k],ny = j + dy[k];	
		if(V[nx][ny]) continue;
		bt(nx,ny,ctr);
	}
	
	unmark(i,j);
}


int main(){
	while(scanf("%d %d",&m,&n) == 2 && m && n){
		int ctr = 0;
		range(i,1,m) scanf("%s",G[i] + 1);		
		range(i,0,m + 1) range(j,0,n + 1) V[i][j] = 0,row[i] = col[j] = 0;		
		range(i,0,m + 1) {
			range(j,0,n + 1){
				if(i == 0 || i == m + 1 || j == 0 || j == n + 1 || G[i][j] == '#') V[i][j] = 1;
				ctr += !V[i][j];
				row[i] += j != 0 && j != n + 1 && V[i][j];
				col[j] += i != 0 && i != m + 1 && V[i][j];
			}
		}
		range(i,1,m) range(j,1,n){
			degree[i][j] = 0;
			loop(k,4) {
				int nx = i + dx[k],ny = j + dy[k];		
				degree[i][j] += !V[nx][ny];
			}
		}	
		ans = 0;
		bt(m,1,ctr);
		printf("%d\n",ans);
	}	
	return 0;
}
