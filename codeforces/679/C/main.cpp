#pragma GCC optimize ("O3")
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

const int MAX = 510;
char grid[MAX][MAX];
int n,k;
int siz[MAX*MAX],id[MAX][MAX],id_ctr;
int cnt[MAX*MAX],vis[MAX][MAX];
int zero[MAX][MAX];

void flood_fill(int x,int y,int id){
	vis[x][y] = 1;
	::id[x][y] = id;
	siz[id] ++;

	for(int dx = -1;dx <= 1;dx++)
		for(int dy = -1;dy <= 1;dy++)
			if(abs(dx) + abs(dy) == 1) {
				int nx = x + dx,ny = y + dy;
				if(nx <= 0 || nx > n || ny <= 0 || ny > n || vis[nx][ny] || grid[nx][ny] != '.') continue;
				flood_fill(nx,ny,id);
			}
}

void pad(){
	fill(grid[0],grid[0] + n + 2,'#');
	fill(grid[n+1],grid[n+1] + n + 2,'#');
	range(i,1,n) grid[i][0] = grid[i][n+1] = '#';
	fill(id[0],id[0] + n + 2,1);
	fill(id[n+1],id[n+1] + n + 2,1);
	range(i,1,n) id[i][0] = id[i][n+1] = 1;
	id_ctr = 1;
}


int main(){
	#ifdef HOME
		freopen("in.in", "r", stdin);
	#endif
	vi aux(4);
	scanf("%d %d",&n,&k);
	if(k == n) {
		cout << n*n << endl;
		return 0;
	}
	range(i,1,n) scanf("%s",grid[i]+1);
	pad();
//	loop(i,n+2) puts(grid[i]);
	range(i,1,n) range(j,1,n) if(!vis[i][j] && grid[i][j] == '.') flood_fill(i,j,++id_ctr);
	range(i,0,n+1){
		range(j,0,n+1) {
			zero[i][j] = grid[i][j] == 'X';
			if(i) zero[i][j] += zero[i-1][j];
			if(j) zero[i][j] += zero[i][j-1];
			if(i && j) zero[i][j] -= zero[i-1][j-1];
		}
	//	prArr(zero[i],n+2,int);
	}
	int ans = 0;
	n += 2;
	k += 2;

	for(int row = 0;row <= n - k;row++){
		// init
		int tmp = 0;
		for(int c = 0;c < k-1;c++)
			for(int i = 0;i < k;i++) {
				int cur = id[row+i][c];
				if(!cnt[cur]) tmp += siz[cur];
				cnt[cur]++;
			}



		// process
		for(int c = k-1;c < n;c++){
			//trim
			if(c != k-1) {
				for(int i = 0;i < k;i++) {
					int cur = id[row+i][c-k];
					if(cnt[cur] == 1) tmp -= siz[cur];
					cnt[cur]--;
				}
			}

			//append
			for(int i = 0;i < k;i++) {
				int cur = id[row+i][c];
				if(!cnt[cur]) tmp += siz[cur];
				cnt[cur]++;
			}
			int val = tmp ,cntX = 0;
			aux[0] = id[row][c-k+1];
			aux[1] = id[row+k-1][c-k+1];
			aux[2] = id[row][c];
			aux[3] = id[row+k-1][c];
			for(int x : aux){
				if(cnt[x] == 1) val -= siz[x];
				cnt[x]--;
			}
			for(int x : aux) cnt[x]++;
			int r1 = row+1,r2 = row + k - 2,c1 = c - k + 2,c2 = c - 1;
			cntX += zero[r2][c2];
			if(r1) cntX -= zero[r1-1][c2];
			if(c1) cntX -= zero[r2][c1-1];
			if(r1 && c1) cntX += zero[r1-1][c1-1];
			ans = max(ans,val + cntX);
		//	cerr << row << " " << c - k + 1 << " -> " << val << " " << cntX << " -> " << val + cntX << " because " << r1 << " " << c1 << " " << r2 << " " << c2 << endl;
		}
		for(int c = n-k;c < n;c++) {
			for(int i = 0;i < k;i++) {
				int cur = id[row+i][c];
				if(cnt[cur] == 1) tmp -= siz[cur];
				cnt[cur]--;
			}
		}
		assert(tmp == 0);
	}
	cout << ans << endl;
	return 0;
}
