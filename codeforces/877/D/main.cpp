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

const int MAX = 1024;
int n,m,k;
char grid[MAX][MAX];
set<int> row[MAX],col[MAX];
queue<pi> q;
int dist[MAX][MAX];
int cnt_row[MAX][MAX],cnt_col[MAX][MAX];

inline bool inRange(int x,int s,int e) {
	return s <= x && s <= e;
}

inline bool inGrid(int x,int y) {
	return inRange(x,0,n-1) && inRange(y,0,m-1);
}

inline bool valid(int a,int b,int *cnt) {
	if(a > b) swap(a,b);
	return (cnt[b] - (a ? cnt[a - 1] : 0)) == 0;
}

void work(int x,int y,set<int> * A,set<int> *B,int *cnt,vector<pi> & ret,bool rev) {
	while(1) {
		auto p = A[x].lower_bound(y);
		if(p == A[x].end()) break;
		if(abs(*p - y) > k) break;
		if(!valid(*p,y,cnt)) break;
		int ty = *p;
		pi tmp = mp(x,ty);
		if(rev) swap(tmp.xx,tmp.yy);
		ret.pb(tmp);
		A[x].erase(ty);
		B[ty].erase(x);
	}
	while(1) {
		auto p = A[x].lower_bound(y);
		if(p == A[x].begin()) break;
		--p;
		if(!valid(*p,y,cnt)) break;
		if(abs(*p - y) > k) break;
		int ty = *p;
		pi tmp = mp(x,ty);
		if(rev) swap(tmp.xx,tmp.yy);
		ret.pb(tmp);
		A[x].erase(ty);
		B[ty].erase(x);
	}
}

vector<pi> getnext(int x,int y) {
	vector<pi> ret;
	work(x,y,row,col,cnt_row[x],ret,0);
	work(y,x,col,row,cnt_col[y],ret,1);
	return ret;
}

int main(){
	#ifdef HOME
		freopen("in.in", "r", stdin);
	#endif
	scanf("%d %d %d",&n,&m,&k);
	loop(i,n) scanf("%s",grid[i]);
	pi S,E;
	scanf("%d %d",&S.xx,&S.yy); S.xx--,S.yy--;
	scanf("%d %d",&E.xx,&E.yy); E.xx--,E.yy--;
	if(grid[S.xx][S.yy] == '#' || grid[E.xx][E.yy] == '#') {
		puts("-1");
		return 0;
	}
	loop(i,n) loop(j,m) {
		cnt_row[i][j] = cnt_col[j][i] = grid[i][j] == '#';
		if(i) cnt_col[j][i] += cnt_col[j][i - 1];
		if(j) cnt_row[i][j] += cnt_row[i][j - 1];
	}
	memset(dist,-1,sizeof dist);
	loop(i,n) loop(j,m) if(grid[i][j] == '.' && mp(i,j) != S) {
		row[i].insert(j);
		col[j].insert(i);
	}
	dist[S.xx][S.yy] = 0;
	q.push(S);
	while(!q.empty()){
		auto tmp = q.front(); q.pop();
		for(auto nxt : getnext(tmp.xx,tmp.yy)){
			dist[nxt.xx][nxt.yy] = dist[tmp.xx][tmp.yy] + 1;
			q.push(nxt);
		}
	}
	cout << dist[E.xx][E.yy] << endl;
	return 0;
}
