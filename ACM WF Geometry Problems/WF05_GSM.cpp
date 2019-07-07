#ifdef ACTIVE
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

const int oo = 1 << 20;
int B,C,R,Q;
pi bts[50],city[50],road[250];
int road_cost[250];
int dist[50][50];
int id[201][201],m;
pair<pi,pi> lines[201*201];
queue<pi> q;

bool final_case(){
	return B==0 && C==0 && R==0 && Q==0;
}
void bfs(){
	fill(&id[0][0],&id[201][0],-1);
	for(int b = 0;b < B;b++) {
		int x = bts[b].xx + 100;
		int y = bts[b].yy + 100;
		q.push(mp(x,y));
		id[x][y] = b;
	}
	for(;!q.empty();q.pop()){
		pi cur = q.front();
		for(int dx = -1;dx <= 1;dx++)
			for(int dy = -1;dy <= 1;dy++) {
				int nx = cur.xx + dx,ny = cur.yy + dy;
				if(nx < 0 || nx > 200 || ny < 0 || ny > 200) continue;
				if(id[nx][ny] != -1) continue;
				id[nx][ny] = id[cur.xx][cur.yy];
				q.push(mp(nx,ny));
			}
	}
	m = 0;
	for(int x = 0;x <= 200;x++) {
		int yp = 0,y = yp;
		while(y <= 200 && id[x][yp] == id[x][y]) y++;
		lines[m++] = mp(mp(x,yp),mp(x,y-1));
		yp = y;
	}
}

int ccw(pi o,pi a,pi b) {
	a.xx -= o.xx,a.yy -= o.yy;
	b.xx -= o.xx,b.yy -= o.yy;
	return a.xx*b.yy - a.yy*b.xx;
}
int sgn(pi o,pi a,pi b) {
	int x = ccw(o,a,b);
	return (x > 0) - (x < 0);
}

bool inbetween(int l,int r,int x) {
	if(l > r) swap(l,r);
	return l <= x && x <= r;
}

bool inbetween(pi a,pi b,pi p) {
	if(a.xx == b.xx) {
		if(a.xx != p.xx) return 0;
		return inbetween(a.yy,b.yy,p.yy);
	}
	return inbetween(a.xx,b.xx,p.xx);
}
bool intersect(pi a,pi b,pi p,pi q) {
	if(a.xx > b.xx) swap(a,b);
	if(p.xx > q.xx) swap(p,q);
	if(a.xx > p.xx) {
		swap(a,p);
		swap(b,q);
	}
	int s1 = sgn(a,b,p),s2 = sgn(a,b,q);
	int s3 = sgn(p,q,a),s4 = sgn(p,q,b);
	if(s1 && s2 && s3 && s4) return s1 != s2 && s3 != s4;
	if(s1 == 0) return inbetween(a,b,p);
	if(s2 == 0) return inbetween(a,b,q);
	if(s3 == 0) return inbetween(p,q,a);
	return inbetween(p,q,b);
}
int get_cost(pi fr,pi to) {
	static unordered_set<int> vis;
	if(fr.xx > to.xx) swap(fr,to);
	vis.clear();
	for(int i = 0;i < m;i++) {
		pi p = lines[i].xx,q = lines[i].yy;

		if(intersect(p,q,fr,to))
			vis.insert(id[p.xx][p.yy]);
	}
	return vis.size();
}
void floyd(){
	loop(i,C) loop(j,C) dist[i][j] = oo*(i != j);
	loop(r,R) {
		int i = road[r].xx,j = road[r].yy;
		dist[i][j] = dist[j][i] = min(dist[i][j],road_cost[r]);
	}
	loop(k,C) loop(i,C) loop(j,C)
			dist[i][j] = min(dist[i][j],dist[i][k] + dist[k][j]);
}
int main(int argc,char **argv){
#ifdef HOME
	freopen("in.in","r",stdin);
#endif
	for(int t = 1;scanf("%d %d %d %d",&B,&C,&R,&Q) == 4 && !final_case();t++) {
		for(int b = 0;b < B;b++)
			scanf("%d %d",&bts[b].xx,&bts[b].yy);
		bfs();

		for(int c = 0;c < C;c++)
			scanf("%d %d",&city[c].xx,&city[c].yy);

		for(int r = 0;r < R;r++) {
			scanf("%d %d",&road[r].xx,&road[r].yy);
//			prp(road[r]);
			road[r].xx--,road[r].yy--;
			road_cost[r] = get_cost(city[road[r].xx],city[road[r].yy]);
//			cerr << " -> " << road_cost[r] << endl;
		}
		floyd();
		printf("Case %d:\n",t);
		for(int q = 0;q < Q;q++) {
			int fr,to; scanf("%d %d",&fr,&to);
			fr--,to--;
			int ans = dist[fr][to];
			if(ans >= oo) puts("Impossible");
			else printf("%d\n",ans);
		}
	}
	return 0;
}
#endif
