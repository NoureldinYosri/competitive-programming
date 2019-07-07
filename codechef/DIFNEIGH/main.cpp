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

int m,n;
int color[50][50];

bool inGrid(int x,int y) {
	return x >= 0 && x < m && y >= 0 && y < n;
}

bool gret(pi p,pi q) {
	if(p.xx + p.yy > q.xx + q.yy) return 1;
	if(p.xx + p.yy < q.xx + q.yy) return 0;
	return p.xx > q.xx;
}

int solve(){
	int k = 0;
	for(int d = 0;d <= m+n-2;d++){
		for(int i = 0;i < m;i++) {
			int j = d - i;
			if(!inGrid(i,j)) continue;
			set<int> S;
			for(int dx = -2;dx <= 2;dx++)
				for(int dy = -2;dy <= 2;dy++)
					if(abs(dx) + abs(dy) == 2) {
						int nx = i + dx,ny = j + dy;
						if(!inGrid(nx,ny)) continue;
						if(gret(mp(nx,ny),mp(i,j))) continue;
						S.insert(color[nx][ny]);
					}
			int c = 0;
			while(S.count(c)) c++;
			k = max(k,c);
			color[i][j] = c;
		}
	}
	++k;
	return k;
}

bool valid(){
	loop(i,m) loop(j,n) {
		set<int> S;
		int ctr = 0;
		int dx[] = {-1,0,1,0},dy[] = {0,1,0,-1};
		loop(r,4) {
			int nx = i + dx[r],ny = j + dy[r];
			if(!inGrid(nx,ny)) continue;
			S.insert(color[nx][ny]);
			ctr++;
		}
		if(ctr != sz(S)){
			cerr << i << " " << j << endl;
			return 0;
		}
	}
	return 1;
}

int solve1(){
	if(max(m,n) <= 2) {
		loop(i,m) loop(j,n) color[i][j] = 0;
		return 1;
	}

	loop(i,m) loop(j,n) {
		int u = 0;
		if(m == 1) u = j/2;
		else u = i/2;
		color[i][j] = u%2;
	}
	return 2;
}

int solve2(){
	if(max(m,n) == 2) {
		loop(i,m) loop(j,n) color[i][j] = i;
		return 2;
	}
	/*
	 * 112233112233
	 * 233112233112
	 */
	vi grid[2];
	int N = max(m,n);
	grid[0] = vi(N,0);
	grid[1] = vi(N,0);
	loop(i,N) grid[0][i] = (i/2)%3;
	loop(i,N) grid[1][i] = ((i+3)/2)%3;
//	print(grid[0],int);
//	print(grid[1],int);
	if(m == 2) {
		loop(i,m) loop(j,n) color[i][j] = grid[i][j];
	}
	else{
		loop(i,m) loop(j,n) color[i][j] = grid[j][i];
	}
	return 3;
}
int G[50][50];


int solve4(){
	loop(i,m) loop(j,n) color[i][j] = G[i][j];

	return 4;
}


int getAnswer(){
	if(min(m,n) == 1) return solve1();
	else if(min(m,n) == 2) return solve2();
	else return solve4();
}

int main(){
#ifdef HOME
	freopen("in.in","r",stdin);
#endif
	m = n = 50;
	solve();
	loop(i,m) {
		copy(color[i],color[i] + n,G[i]);
	}
	int T;
	scanf("%d",&T);
	while(T--) {
		scanf("%d %d",&m,&n);
		int k = getAnswer();
		printf("%d\n",k);
		loop(i,m) loop(j,n) printf("%d%c",color[i][j]+1," \n"[j==n-1]);
		assert(valid());
		assert(k <= 4);
	}
	return 0;
}
