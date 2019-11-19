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
using namespace std;


const int MAX = 111;
int R,C,K;
char grid[MAX][MAX];
string out = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";

void getNext(int & i,int & j){
	while(grid[i][j] != '#'){
		j++;
		if(j == C){
			j = 0;
			i++;
		}
	}
}

void mark(int i,int j,int & v,char c){
	//if(grid[i][j] != '.')
//		cout << c << ": " << i << " " << j << endl;
	v -= grid[i][j] == '#';
	grid[i][j] = c;
}

int dx[] = {0,1,0,-1};
int dy[] = {1,0,-1,0};

void dfs(int i,int j,char c,bool isBegin){
	if(i < 0 || i >= R || j < 0 || j >= C) return;
	if(!isBegin && grid[i][j] != '.' && grid[i][j] != '#') return;
	grid[i][j] = c;
	loop(k,4) dfs(i+dx[k],j+dy[k],c,0);
}


vector<vector<pi>> spirals;

bool done[MAX][MAX];

bool inGrid(int x,int y){
	return x >= 0 && x < R && y >= 0 && y < C;
}

void follow(int i,int j,vector<pi> & V){
	int x = i,y = j;
	done[i][j] = 1;
	V.emplace_back(i,j);
	loop(k,4){
		while(1){
			int nx = x + dx[k];
			int ny = y + dy[k];
			if(inGrid(nx,ny) && !done[nx][ny]){
				x = nx;
				y = ny;
				done[x][y] = 1;
				V.emplace_back(x,y);
			}
			else break;			
		}
	}
}

void make_spirals(){
	spirals.clear();
	for(int i = 0;i < R;i++)
		for(int j = 0;j < C;j++)
			done[i][j] = 0;
	for(int i = 0;i < R;i++)
		for(int j = 0;j < C;j++)
			if(!done[i][j]){
				vector<pi> V;
				follow(i,j,V);
				spirals.push_back(V);
		//		for(auto p : V)
		//			cout << p << " ";
		//		cout << endl;
			}
			
}

bool isNeighbours(int a,int b,int c,int d){
	if(a == -1 || b == -1) return 1;
	return (abs(a-c) + abs(b-d)) <= 1;
}

void solve(){
	spirals.clear();
	make_spirals();
	int cnt = 0;
	loop(r,R) loop(c,C) if(grid[r][c] == '#') cnt++;
	int v = cnt/K;
	int k = cnt%K;
	int q = 0;

//	cout << v << " " << k << endl;
	loop(p,K){
		int target = v + (p < k);
		char c = out[q++];
		int i = -1,j = -1;
		while(target){
			assert(spirals.size());
			vector<pi> *V = &spirals.back();
			while(V->empty()) {
				spirals.pop_back();
				assert(spirals.size());
				V = &spirals.back();
			}
			while(!isNeighbours(i,j,V->back().first,V->back().second))
				rotate(V->begin(),V->begin() + 1,V->end());
			auto p = V->back(); 
			V->pop_back();
			i = p.first,j = p.second;
			mark(i,j,target,c);
		}
		assert(target == 0);
	}
	loop(a,R) loop(b,C) if(grid[a][b] != '.' && grid[a][b] != '#') dfs(a,b,grid[a][b],1);
}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	int T; scanf("%d",&T);
	while(T--){
		scanf("%d %d %d",&R,&C,&K);
		loop(r,R) scanf("%s",grid[r]);
		loop(r,R) loop(c,C) if(grid[r][c] == 'R') grid[r][c] = '#';
		solve();
		loop(r,R) puts(grid[r]);		
	}
	return 0;
}

