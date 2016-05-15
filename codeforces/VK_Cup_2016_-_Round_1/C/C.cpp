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

vi G[1 << 20]; int P[1 << 20]; int D[1 << 20];
vector<pi> E;
int n,d,h;
	
void add(int a,int b){
	E.pb(mp(a,b));
	G[a].pb(b);
	G[b].pb(a);	
}

int bfs(int & s){
	fill(P,P + n + 1,0);
	D[s] = 0;
	queue<int> q; q.push(s);
	int l = s;	
	while(!q.empty()){
		int u = q.front(); q.pop();
		for(int v : G[u]) if(P[u] != v){
			P[v] = u;
			D[v] = D[u] + 1;
			q.push(v);
			l = v;
		}
	}
	s = l;
	//cerr << D[l] << endl;
	return D[l];
}


bool check(){
	int s = 1;
	if(bfs(s) != h) return 0;
	return bfs(s) == d;
}

int main(){
	cin >> n >> d >> h;
	int zp,rp = 1;
	for(int u = 1;u <= h;u++) {
		add(u,u + 1);
		int H = h - u;
		if(d - H <= H && n - (h + 1) >= d - H) rp = u + 1;
	}
	//cerr << rp << endl;
	zp = rp;
	if(rp > h + 1) {
		puts("-1");
		return -1;
	}
	int r = h + 2,H = min(h - rp + 1,d - (h - rp + 1));
	while(r <= n && H--){
	//	cerr << rp << " " << r << endl;
		add(rp,r);
		rp = r++;
	}
	//for(auto e : E) cerr << e.xx << " " << e.yy << endl;
	//cerr << endl;
	rp = zp;
	while(r <= n) add(r++,rp);
	if(check()) {
		for(auto e : E) printf("%d %d\n",e.xx,e.yy);
	}
	else puts("-1");
	return 0;
}
