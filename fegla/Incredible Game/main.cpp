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
#define pl pair<ll,ll>
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

pi S,E;
pi rocks[1 << 20];
int m,n,N;
set<pi> vis;
vi row[1 << 20],col[1 << 20];

bool get_next(vi & V,int t,int & v){
	//print(V,int);
	assert(!binary_search(all(V),t));
	auto p = upper_bound(all(V),t);
	v = *p - 1;
	assert(p != V.end());
	return !binary_search(all(V),v);
}
bool get_prv(vi & V,int t,int & v){
	//print(V,int);
	assert(!binary_search(all(V),t));
	auto p = upper_bound(all(V),t);
	assert(p != V.begin());
	--p;
	v = *p + 1;
	return !binary_search(all(V),v);
}

bool inrange(int x1,int x2,int y1,int y2){
	assert(x1 <= x2 && y1 <= y2);
	return x1 <= E.xx && E.xx <= x2 && y1 <= E.yy && E.yy <= y2;
}

int solve(){
	vis.clear();
	loop(i,m) row[i].clear();
	loop(i,n) col[i].clear();
	loop(i,N) row[rocks[i].xx].pb(rocks[i].yy);
	loop(i,N) col[rocks[i].yy].pb(rocks[i].xx);
	loop(i,m) {
		row[i].pb(-1);
		row[i].pb(n);
		sort(all(row[i]));
		row[i].resize(unique(all(row[i])) - row[i].begin());
	}
	loop(i,n) {
		col[i].pb(-1);
		col[i].pb(m);
		sort(all(col[i]));
		col[i].resize(unique(all(col[i])) - col[i].begin());
	}
	queue<pi> q;
	q.push(S); vis.insert(S);
	for(int dist = 0;!q.empty();dist++){
		for(int i = 0,L = q.size();i < L;i++){
			pi cur = q.front(); q.pop();
	//		prp(cur); cerr << endl;
			if(cur == E) return dist;
			int x,y;
	//		cerr << "entering 1" << endl;
			if(get_next(row[cur.xx],cur.yy,y)) {
				x = cur.xx;
				if(vis.find(mp(x,y)) == vis.end()) {
	//				cerr << "inserting " << x << " " << y << endl;
					vis.insert(mp(x,y));
					q.push(mp(x,y));
				}
				if(inrange(x,x,cur.yy,y)) return dist + 1;
			}
	//		cerr << "entering 2" << endl;
			if(get_prv(row[cur.xx],cur.yy,y)){
				x = cur.xx;
				if(vis.find(mp(x,y)) == vis.end()) {
	//				cerr << "inserting " << x << " " << y << endl;
					vis.insert(mp(x,y));
					q.push(mp(x,y));
				}
				if(inrange(x,x,y,cur.yy)) return dist + 1;
			}
	//		cerr << "entering 3" << endl;
			if(get_next(col[cur.yy],cur.xx,x)){
				y = cur.yy;
				if(vis.find(mp(x,y)) == vis.end()) {
	//				cerr << "inserting " << x << " " << y << endl;
					vis.insert(mp(x,y));
					q.push(mp(x,y));
				}
				if(inrange(cur.xx,x,y,y)) return dist + 1;
			}
	//		cerr << "entering 4" << endl;
			if(get_prv(col[cur.yy],cur.xx,x)){
				y = cur.yy;
				if(vis.find(mp(x,y)) == vis.end()) {
	//				cerr << "inserting " << x << " " << y << endl;
					vis.insert(mp(x,y));
					q.push(mp(x,y));
				}
				if(inrange(x,cur.xx,y,y)) return dist + 1;
			}
	//		cerr << "finished" << endl;
		}
	}
	return -1;
}

int main(){
	freopen("maze.in", "r", stdin);
	int T; scanf("%d",&T);
	while(T--){
		scanf("%d %d %d",&m,&n,&N);
		scanf("%d %d",&S.xx,&S.yy);
		scanf("%d %d",&E.xx,&E.yy);
		loop(i,N) scanf("%d %d",&rocks[i].xx,&rocks[i].yy);
		printf("%d\n",solve());
	}
	return 0;
}
