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

const int MAX = 1000 + 10,MXLG = 15;
int L,n;
char line[5*MAX];
char grid[MAX][MAX];
int oL,lg;
int dp[2][MAX][MAX];


bool move(int & x,int & y,int i){
	if(grid[x][y] != '.') return 0;
	if(line[i] == 'U') x--;
	else if(line[i] == 'D') x++;
	else if(line[i] == 'R') y++;
	else if(line[i] == 'L') y--;
	return 0 <= x && x < n && 0 <= y && y < n && grid[x][y] == '.';
}




int solve(){
	memset(dp,0,sizeof dp);
	int one = 0,other = 1,x,y;
	for(int pos = L-1;pos >= 0;pos--){
		loop(i,n) loop(j,n){
			if(grid[i][j] == '.'){
				x = i;y = j;
				if(move(x,y,pos)) dp[one][i][j] = 1 + dp[other][x][y];
				else dp[one][i][j] = 0;
			}
			else dp[one][i][j] = 0;
		}
		one ^= other ^= one ^= other;
	}
	/*
	 loop(i,n) {
		loop(j,n){
			if(grid[i][j] == '#') cerr << grid[i][j] << " ";
			else cerr << dp[other][i][j] << " ";
		}
		cerr << endl;
	}
	*/
	int ret = 0;
	loop(i,n) loop(j,n) ret ^= dp[other][i][j];
	return ret;
}

int main(){
	#ifndef ONLINE_JUDGE
		freopen("input.in", "r", stdin);
		freopen("output.out", "w", stdout);
	#endif
	int T; scanf("%d",&T);
	while(T--){
		scanf("%d %d",&L,&n);
		scanf("%s",line);
		loop(i,n) scanf("%s",grid[i]);
		printf("%d\n",solve());
	}
	return 0;
}
