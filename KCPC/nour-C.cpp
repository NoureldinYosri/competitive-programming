#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define range(i,a,b) for(int i = (a);i <= (b);i++)
#define rrep(i,n) for(int i = (n);i >= 0;i--)
#define rran(i,a,b) for(int i = (b);i >= (a);i--)
#define step(i,a,b,d) for(int i = (a);i <= (b); i += d)
#define all(A) A.begin(),A.end()
#define pb push_back
#define mp make_pair
#define sz(A) A.size()
#define len(A) A.length()
#define print(A,t) cout << #A << ": "; copy(all(A),ostream_iterator<t>(cout," " )); cout << endl
#define pi pair<int,int>
#define point pi
#define vi vector<int>
#define ll long long
#define pl pair<ll,ll>
#define pre() cin.tie(0),cout.tie(0),ios_base::sync_with_stdio(0)
#define popcnt(x) __builtin_popcount(x)
using namespace std;

int D[110][110],V[110][110],m,n;
pi nxt[110][110],other_nxt[110][110];
vector<pi> cells[26];
int dx[] = {0,0,1,-1},dy[] = {-1,1,0,0};
char G[110][110];

int solve(pi S,pi T){
	fill(&D[0][0],&D[m][0],0);
	fill(&V[0][0],&V[m][0],0);
	deque<pi> dq;
	dq.pb(S);
	D[S.first][S.second] = 1;
	while(!dq.empty()){
		pi u = dq.front(); dq.pop_front();
		if(V[u.first][u.second]) continue;
		V[u.first][u.second] = 1;
		if(u == T) return D[u.first][u.second] - 1;
		if(nxt[u.first][u.second].first != -1){
			pi v = nxt[u.first][u.second];
			if(!V[v.first][v.second]){
				dq.push_front(v);
				D[v.first][v.second] = D[u.first][u.second];
			}
		}
		if(other_nxt[u.first][u.second].first != -1){
			pi v = other_nxt[u.first][u.second];
			if(!V[v.first][v.second]) {
				dq.push_front(v);
				D[v.first][v.second] = D[u.first][u.second];
			}
		}
		for(int i = 0;i < 4;i++){
			pi v = u;
			v.first += dx[i];
			v.second += dy[i];
			if(v.first == -1 || v.first == m || v.second == -1 || v.second == n)
				continue;
			if(D[v.first][v.second]) continue;
			if(G[v.first][v.second] == '*') continue;
			D[v.first][v.second] = D[u.first][u.second] + 1;
			dq.pb(v);
		}
	}
	return 1 << 30;
}

int main(){
	int T; pi S,E;
	scanf("%d",&T);
	while(T--){
		scanf("%d %d",&m,&n);
		fill(&nxt[0][0],&nxt[m][0],mp(-1,-1));
		fill(&other_nxt[0][0],&other_nxt[m][0],mp(-1,-1));
		loop(i,26) cells[i].clear();
		loop(i,m){
			scanf("%s",G[i]);
			loop(j,n)
				if(G[i][j] == 'S') S = mp(i,j);
				else if(G[i][j] == 'T') E = mp(i,j);
				else if('a' <= G[i][j] && G[i][j] <= 'z') cells[G[i][j] - 'a'].pb(mp(i,j)); 
		}
		loop(i,26){
			loop(j,sz(cells[i])) {
				nxt[cells[i][j].first][cells[i][j].second] = cells[i][(j + 1)%sz(cells[i])];
			}
			int j = sz(cells[i]) - 1;
			if(sz(cells[i]) && i < 25 && sz(cells[i + 1])) {
				other_nxt[cells[i][j].first][cells[i][j].second] = cells[i + 1][0];
			}
		}
		int ans = solve(S,E);
		ans = (ans == (1 << 30)) ? -1 : ans;
		printf("%d\n",ans); 
	}
	return 0;
}
