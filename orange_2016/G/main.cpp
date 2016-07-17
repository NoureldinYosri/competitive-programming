#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define range(i,a,b) for(int i = (a);i <= (b);i++)
#define rrep(i,n) for(int i = (n);i >= 0;i--)
#define rran(i,a,b) for(int i = (b);i >= (a);i--)
#define all(A) A.begin(),A.end()
#define PI acos(-1)
#define pb push_back
#define mp make_pair
#define sz(A) A.size()
#define vi vector<int>
#define vl vector<long>
#define vd vector<double>
#define ll long long
#define pi pair<int,int>
#define point pair<double,double>
#define pl pair<ll,ll>
#define popcnt(x) __builtin_popcount(x)
#define LSOne(x) ((x) & (-(x)))
#define xx first
#define yy second
#define PQ priority_queue
#define print(A,t) cerr << #A << ": "; copy(all(A),ostream_iterator<t>(cerr," " )); cerr << endl
#define prp(p) cerr << "(" << (p).first << " ," << (p).second << ")";
#define prArr(A,n,t)  cerr << #A << ": "; copy(A,A + n,ostream_iterator<t>(cerr," " )); cerr << endl
#define PRESTDIO() cin.tie(0),cerr.tie(0),ios_base::sync_with_stdio(0)
using namespace std;

const int MAX = 10010;
char G[50][51],line[MAX],tmpZ[MAX];
int adj[50*50][4];
int m,n,L;
int dx[] = {0,0,-1,1},dy[] = {1,-1,0,0};
int D[MAX*2 + 1][50*50];

void create_graph(){
	loop(x,m) loop(y,n){
		loop(i,4){
			int nx = x,ny = y;		
			do{
				nx += dx[i],ny += dy[i];
				if(nx < 0 || nx >= m || ny < 0 || ny >= n) break;
			}while(G[x][y] == G[nx][ny]);
			if(nx < 0 || nx >= m || ny < 0 || ny >= n) {
		
			}
			adj[n*x + y].pb(nx*n + ny);
		}
	}
}


void pre(){
	create_graph();
	L = strlen(tmpZ);
	int idx = 0;	
	loop(i,L){
		if(tmpZ[i] == '*' || tmpZ[i] == '#' || islower(tmpZ[i])) line[idx++] = tmpZ[i];
		else {
			line[idx++] = '#';
			line[idx++] = tolower(tmpZ[i]);
		}
	}
	line[idx++] = '*';
	L = idx;
	fill(D[0],D[L + 1],1 << 29);
}

int solve(){
	typedef pair<int,pi> node;
	PQ<node ,vector<node>,greater<node> > pq;
	pq.push(mp(0,mp(0,0)));
	D[0][0] = 0;
	while(!pq.empty()){
		auto u = pq.top(); pq.pop();
		int w = u.xx,idx = u.yy.xx,x = u.yy.yy/n,y = u.yy.yy%n,cell = u.yy.yy;
		if(idx == L) return u.xx;
		if(w > D[idx][cell]) continue;
		if(G[x][y] == line[idx] && D[idx + 1][cell] > w + 1) {
			D[idx + 1][cell] = w + 1;
			pq.push(mp(w + 1,mp(idx + 1,cell)));
		}
		for(auto v : adj[cell]){
			if(D[idx][v] > D[idx][cell] + 1){
				D[idx][v] = D[idx][cell] + 1;
				pq.push(mp(w + 1,mp(idx,v)));
			}
		}
	}
	return -1;
}

int main(){
	scanf("%d %d",&m,&n);
	loop(i,m) scanf("%s",G[i]);
	scanf("%s",tmpZ); 
	pre();
	int ans = solve();
	cout << ans << endl;
	cerr << ans << endl;
	return 0;
}
