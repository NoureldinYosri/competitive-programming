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



#define check(msk,p) (msk & (1 << p))
const int MAXN = 9,patC = 4;
int m,n,best;
char grid[9][10],ans[9][10];
char pat[5][3][4] = {
		 {"#..",
		  "###",
		  "#.."},

		{"###",
		 ".#.",
		 ".#."},



		  {"..#",
		   "###",
		   "..#"},

		{".#.",
		 ".#.",
		 "###"},

		{"...",
		 "...",
  		 "..."}
};

inline bool can(int r,int c,int t) {
	loop(i,3) loop(j,3)
			if(grid[r+i][c+j] != '.' && pat[t][i][j] != '.')
				return 0;
	return 1;
}

void put(int r,int c,int t,char ch) {
//	cerr << "=============================" << endl;
//	loop(i,m) cerr << grid[i] << endl;
	loop(i,3)
		loop(j,3)
			if(pat[t][i][j] == '#')
				grid[r+i][c+j] = ch;
//	cerr << "->" << endl;
//	loop(i,m) cerr << grid[i] << endl;
}
void unput(int r,int c,int t) {
	loop(i,3)
		loop(j,3)
			if(pat[t][i][j] == '#')
				grid[r+i][c+j] = '.';
}

void bt(int r,int c,int d) {
	if((n*m)/(r*c + r + c + 1) * d + 2 < best) return;
	if(c == n-2) return bt(r+1,0,d);
	if(r == m-2) {
		if(d > best) {
			best = d;
			loop(i,m) strcpy(ans[i],grid[i]);
		}
		return;
	}
	for(int t = 0;t < patC;t++)
		if(can(r,c,t)){
			put(r,c,t,'A' + d);
			bt(r,c+1,d + 1);
			unput(r,c,t);
		}
	bt(r,c+1,d);
}

int main(int argc,char **argv){
#ifdef HOME
	freopen("in.in","r",stdin);
#endif
	cin >> m >> n;
	loop(i,m) loop(j,n) ans[i][j] = grid[i][j] = '.';
	if(m <= 2 || n <= 2) cout << 0 << endl;
	else {
		bt(0,0,0);
		printf("%d\n",best);
	}
	loop(r,m) puts(ans[r]);
	return 0;
}
