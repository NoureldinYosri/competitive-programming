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

vi G[500];
int C[500][500];
int F[500][500];
int J,P,S,K,N;
int V[500],Pa[500];
int JP[20][20],PS[20][20];
int WHO[1000][2];

bool forward(int u,int v){
	if(v < N) return u < v;
	return v - u == 250;
}

int augment(int *P,int L){
	//prArr(P,L,int);
	int mn = INT_MAX;
	loop(i,L - 1) {
		int u = P[i],v = P[i + 1];	
		mn = min(mn,C[u][v] - F[u][v]);
	}
	loop(i,L - 1) {
		int u = P[i],v = P[i + 1];	
	//	cerr << u << " " << v << " " << forward(u,v) << endl;
		F[u][v] += mn;
		F[v][u] -= mn;
	}
	//cerr << mn << endl;
	return mn;
}

bool getPath(int *P,int & L){
	L = 0;
	fill(V,V + 500,0);
	fill(Pa,Pa + 500,-1);
	queue<int> q; q.push(0); V[0] = 1;
	while(!q.empty()){
		int u = q.front();
		q.pop();
		for(auto v : G[u]){
			//if(V[v]) continue;
		//	cerr << u << " -> " << v << " " << C[u][v] << " " << F[u][v] << " " << V[v] << endl;
			if(C[u][v] - F[u][v] > 0 && !V[v]){
				Pa[v] = u;
				V[v] = 1;
				q.push(v);
			}
		}
	}
	if(Pa[N - 1] == -1) {
	//	cerr << "No Path" << endl;	
		return 0;
	}
	int u = N - 1;
	while(u != -1){
		P[L++] = u;
		u = Pa[u];
	}
	reverse(P,P + L);
	return 1;
}

int mf(){
	int f = 0;
	int P[10],L;
	//cerr << "start" << endl;
	while(getPath(P,L)) f += augment(P,L);
	//cerr << "done" << endl;
	return f;
}

void init(){
	loop(i,500) G[i].clear();
	loop(i,500) loop(j,500) C[i][j] = F[i][j] = 0;
	int idx = 1;
	range(i,1,J) range(j,1,P) {
		WHO[idx][0] = i;
		WHO[idx][1] = j;	
		JP[i][j] = idx++;
	}
	range(i,1,P) range(j,1,S) {
		WHO[idx][0] = i;
		WHO[idx][1] = j;	
		PS[i][j] = idx++;
	}
	N = ++idx;
	//cerr << J << " " << P << " " << S << endl;
	cerr << N << endl; // check for large
}

void addEdge(int a,int b,int c){
	//cerr << a << " -> " << b << endl;
	G[a].pb(b);
	G[b].pb(a);
	C[a][b] = c; C[b][a] = 0;
	F[a][b] = 0; F[b][a] = 0;
}

inline void addNode(int u){addEdge(u,u + 250,K);}

void constructGraph(){
	range(i,1,J) range(j,1,P) addNode(JP[i][j]);
	range(i,1,P) range(j,1,S) addNode(PS[i][j]);

	range(i,1,J) range(j,1,P) addEdge(0,JP[i][j],1 << 20);
	range(i,1,J) range(j,1,P) range(k,1,S) addEdge(JP[i][j] + 250,PS[j][k],1);
	range(i,1,P) range(j,1,S) addEdge(PS[i][j] + 250,N - 1,1 << 20);
}

void PrintALL(){
	range(i,1,J) range(j,1,P) range(k,1,S) if(F[JP[i][j] + 250][PS[j][k]]) printf("%d %d %d\n",i,j,k);
}

int main(){
	int T;
	scanf("%d",&T); //T = 1;
	loop(t,T){
		scanf("%d %d %d %d",&J,&P,&S,&K); 
		init();
		constructGraph();
		printf("Case #%d: %d\n",t + 1,mf());
		PrintALL();
	}		
	return 0;
}