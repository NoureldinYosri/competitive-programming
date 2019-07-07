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

void get_col(int r,vi & Col,int cell){
	int c = 0;
	loop(i,V+1) {
		int c0 = c;
		while(c < C && cnt[r][c] - (c0 ? cnt[r][c0-1] : 0) < cell)
			c++;
		if(c == C || cnt[r][c] - (c0 ? cnt[r][c0-1] : 0) != cell)
			break;
		Col.push_back(c);
	}
}

bool valid_col(int r0,int r,const vi & Col,int cell) {
	int prv = -1;
	for(int c : Col) {
		int ctr = cnt[r][c];
		if(r0) ctr -= cnt[r0-1][c];
		if(prv != -1) ctr -= cnt[r][prv];
		if(r0 && prv!=-1) ctr += cnt[r0-1][prv];
		if(ctr != cell) return 0;
		prv = c;
	}
	return 1;
}

bool solve(){
	int tot = get_count();
	int num = (H+1)*(V+1);
	if(tot%num != 0) return 0;
	int cell = tot/num;
	int r = 0;
	vi Col,Row;
	loop(i,H+1) {
		int target = cell * (V+1);
		int r0 = r;
		while(r < R && (cnt[r][C-1] - (r0 ? cnt[r0-1][C-1] : 0)) < target)
			r++;
		if(r == R) return 0;
		Row.push_back(r);
	}

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
		break;
	}
	return 0;
}
