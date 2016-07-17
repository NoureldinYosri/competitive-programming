#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define range(i,a,b) for(int i = (a);i <= (b);i++)
#define rrep(i,n) for(int i = (n);i >= 0;i--)
#define rran(i,a,b) for(int i = (b);i >= (a);i--)
#define step(i,a,b,d) for(int i = (a);i <= (b); i += d)
#define all(A) A.begin(),A.end()
#define PI acos(-1)
#define pb push_back
#define mp make_pair
#define sz(A) A.size()
#define len(A) A.length()
#define vi vector<int>
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
#define pre() cin.tie(0),cerr.tie(0),ios_base::sync_with_stdio(0)
using namespace std;

int D[3001][3001],n,m;
int best_in[3001][10];
int best_out[3001][10];
vi G[3001];
pi V[10];
const int INF = 1 << 28;
	

void bfs(int s){
	fill(&D[s][1],&D[s][n + 1],INF);
	D[s][s] = 0;
	queue<int> q;	q.push(s); 
	while(!q.empty()){
		int u = q.front(); q.pop();
		for(int v : G[u]){
			if(D[s][v] != INF) continue;
			D[s][v] = D[s][u] + 1;
			q.push(v);
		}
	}
}



int main(){
	scanf("%d %d",&n,&m);
	while(m--){
		int a,b;
		scanf("%d %d",&a,&b);
		G[a].pb(b);
	}	
	range(i,1,n) {
		bfs(i);
	//	prArr(D[i] + 1,n,int);
	}
	for(int s = 1;s <= n;s++){
		int idx = 0;		
		for(int e = 1;e <= n;e++){
			if(s != e && D[s][e] != INF) {
				if(idx < 5)  V[idx++] = mp(D[s][e],e);
				else if(V[0].xx < D[s][e]) V[0] = mp(D[s][e],e);
				sort(V,V + idx);			
			}
		}
		reverse(V,V + idx);
		loop(i,min(idx,5)) best_out[s][i] = V[i].yy;
	}
	for(int e = 1;e <= n;e++){
		int idx = 0;		
		for(int s = 1;s <= n;s++){
			if(s != e && D[s][e] != INF) {
				if(idx < 5) V[idx++] = mp(D[s][e],s);
				else if(V[0].xx < D[s][e]) V[0] = mp(D[s][e],s);
				sort(V,V + idx);			
			}
		}
		reverse(V,V + idx);
		loop(i,min(idx,10)) best_in[e][i] = V[i].yy;
	}/*
	range(i,1,n) {
		cerr << i << endl << "best in : " << endl;
		loop(j,5) cerr << best_in[i][j][0] << " " << best_in[i][j][1] << endl;
		cerr << "best out" << endl;	
		loop(j,5) cerr << best_out[i][j][0] << " " << best_out[i][j][1] << endl;
		cerr << "==========================" << endl;	
	}*/
	ll ans = 0;
	int a,b,c,d,x,y;
	for(int s = 1;s <= n;s++){
		for(int e = 1;e <= n;e++){
			if(D[s][e] == INF) continue;
			loop(i,10) loop(j,10){
				int x = best_in[s][i],y = best_out[e][j];			
				if(x == 0 || y == 0) continue;				
				if(s != e && s != x && s != y && e != x && e != y && x != y){
					ll tmp = D[x][s] + D[s][e] + D[e][y];
	//				cerr << x << " " << s << " " << e << " " << y << "\t" << D[x][s] << " " << D[s][e] << " " << D[e][y] << endl;
					if(tmp > ans){
						ans = tmp;
						a = x,b = s,c = e,d = y;
					}
				}
			}	
		}	
	}
	assert(ans > 0);
	//cerr << ans << endl;
	cout << a << " " << b << " " << c << " " << d << endl;
	return 0;
}
