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
int best_in[3001][10][2];
int best_out[3001][10][2];
vi G[3001];
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
	range(i,1,n) bfs(i);
	for(int s = 1;s <= n;s++){
		for(int e = 1;e <= n;e++){
			if(D[s][e] > best_out[s][9][0] && D[s][e] != INF){
				best_out[s][9][0] = D[s][e];
				best_out[s][9][1] = e;
				int i = 9;
				while(i > 0 && best_out[s][i - 1][0] < best_out[s][i][0]){
					swap(best_out[s][i - 1][0],best_out[s][i][0]);
					swap(best_out[s][i - 1][1],best_out[s][i][1]);
					i--;				
				}
			}
		}
	}
	for(int e = 1;e <= n;e++){
		for(int s = 1;s <= n;s++){
			if(D[s][e] > best_in[e][9][0] && D[s][e] != INF){
				best_in[e][9][0] = D[s][e];
				best_in[e][9][1] = s;
				int i = 9;
				while(i > 0 && best_in[e][i - 1][0] < best_in[s][i][0]){
					swap(best_in[e][i - 1][0],best_in[e][i][0]);
					swap(best_in[e][i - 1][1],best_in[e][i][1]);
					i--;				
				}
			}
		}
	}
	/*range(i,1,n) {
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
			loop(i,10) loop(j,10){
				x = best_in[s][i][1];
				y = best_out[e][j][1];
				if(x == INF || y == INF || x == 0 || y == 0) continue;
				if(s != e && s != x && s != y && e != x && e != y && x != y){
					ll tmp = D[x][s] + D[s][e] + D[e][y];
					if(tmp > ans && tmp < INF){
						ans = tmp;
						a = x,b = s,c = e,d = y;
					}
				}
			}	
		}	
	}
	cerr << a << " " << b << " " << c << " " << d << endl;
	assert(ans > 0);
	cout << a << " " << b << " " << c << " " << d << endl;
	return 0;
}
