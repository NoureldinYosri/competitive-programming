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

const int MAX = 50000 + 10;
int rowL[MAX],rowR[MAX];
int colU[MAX],colD[MAX];
int N,M;
char toS[] = "SE";
map<char,int> toB = {{'S',0},{'E',1}};
pi dir[2] = {mp(1,0),mp(0,1)};
char D[MAX << 1],res[MAX << 1];
map<pi,int> mem;



void solve(int x,int y,int t) {
	int ctr[2] = {0};
	for(;t < M;t++) {
		if(mem.count(mp(x,y))) res[t] = toS[mem[mp(x,y)] ^ 1];
		else {
			int d = min(0,1,[ctr](const int & a,const int & b) {
				return ctr[a] < ctr[b];
			});
			res[t] = toS[d];
		}
		ctr[toB[res[t]]]++;
		int d = toB[res[t]];
		x += dir[d].first;
		y += dir[d].second;
	}
}

void solve(){
	mem.clear();
	loop(i,N) rowL[i] = colU[i] = N;
	loop(i,N) rowR[i] = colD[i] = 0;
	int x = 0,y = 0;
	rowL[0] = rowR[0] = 0;
	colU[0] = colD[0] = 0;
	for(int c = 0;c < M;c++) {
		int d = mem[mp(x,y)] = toB[D[c]];
		x += dir[d].first;
		y += dir[d].second;
		rowL[x] = min(rowL[x],y);
		rowR[x] = max(rowR[x],y);
		colU[y] = min(colU[y],x);
		colD[y] = max(colD[y],x);
	}
	solve(0,0,0);
}

int main(int argc,char **argv){
#ifdef HOME
	freopen("in.in","r",stdin);
#endif
	int T; scanf("%d",&T);
	for(int t = 1;t <= T;t++) {
		scanf("%d %s",&N,D);
		M = strlen(D);
		solve();
		printf("Case #%d: %s\n",t,res);
	}
	return 0;
}
