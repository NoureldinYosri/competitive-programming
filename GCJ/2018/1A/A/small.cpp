#ifdef DEBUG
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

const int MAX = 111;
char str[2][20] = {"IMPOSSIBLE","POSSIBLE"};
char G[MAX][MAX];
int R,C,H,V;
int cnt[MAX][MAX];

int get_count(){
	int tot = 0;
	loop(i,R) loop(j,C) {
		tot += G[i][j] == '@';
		cnt[i][j] = G[i][j] == '@';
		if(i) cnt[i][j] += cnt[i-1][j];
		if(j) cnt[i][j] += cnt[i][j-1];
		if(i&&j) cnt[i][j] -= cnt[i-1][j-1];
	}
	return tot;
}

bool solve_small(int cell){
	for(int c = 0;c+1 < C;c++)
		for(int r = 0;r+1 < R;r++) {
			int a = cnt[r][c];
			int b = cnt[R-1][c] - a;
			int c = cnt[r][C-1] - a;
			int d = cnt[R-1][C-1] - a - b - c;
			if(a == cell && b == cell && c == cell && d == cell)
				return 1;
		}
	return 0;
}

bool solve(){
	int tot = get_count();
	int num = (H+1)*(V+1);
	if(tot%num != 0) return 0;
	if(V == 1 && H == 1) return solve_small(tot/num);
	return 1;
}

int main(int argc,char **argv){
#ifdef HOME
	freopen("in.in","r",stdin);
#endif
	int T; scanf("%d",&T);
	range(t,1,T) {
		scanf("%d %d %d %d",&R,&C,&H,&V);
		loop(i,R) scanf("%s",G[i]);
		printf("Case #%d: %s\n",t,str[solve()]);
	}
	return 0;
}
#endif
