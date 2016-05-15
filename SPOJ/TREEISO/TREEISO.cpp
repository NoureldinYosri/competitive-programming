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

const int MAX = 1 << 20;
int N,n;
vi T1[MAX],T2[MAX]; int P1[MAX],P2[MAX];
vi L1[MAX],L2[MAX]; int D[MAX];
vi subt1[MAX],subt2[MAX],*subt;

int bfs(int s,int & u,vi *T,int *P, vi *L){
	u = 1;
	loop(i,n + 1) L[i].clear(),P[i] = -1;	
	queue<int> q; q.push(s); P[s] = 0;
	int d = 0; D[s] = 0; L[0].pb(s);
	while(!q.empty()){
		s = q.front(); q.pop();
		for(int v : T[s])
			if(P[v] == -1){
				P[v] = s;
				d = D[v] = D[s] + 1;
				L[D[v]].pb(u = v);
				q.push(u);
			}
	}	
	return d;
}

void get_centers(vi *T,int *P,vi *L,vi & C){
	int u,d;
	bfs(1,u,T,P,L);
	d = bfs(u,u,T,P,L);
	if(d & 1) C.pb(L[d/2][0]),C.pb(L[d/2+1][0]); 
	else C.pb(L[d/2][0]);
}



bool cmp(const int & a,const int & b){
	return subt[a] < subt[b];
}

bool check(int c1,int c2){
	int u,d1,d2;
	d1 = bfs(c1,u,T1,P1,L1);
	d2 = bfs(c2,u,T2,P2,L2);
	if(d1 != d2) return 0;
	loop(i,n + 1) subt1[i].clear(),subt2[i].clear();
	int d = d1;
	for(;d >= 0;d--){
		if(sz(L1[d]) != sz(L2[d])) return 0;
		for(int v : L1[d]) sort(all(subt1[v]));
		for(int v : L2[d]) sort(all(subt2[v]));
		subt = subt1; sort(all(L1[d]),&cmp);
		subt = subt2; sort(all(L2[d]),&cmp);
		loop(i,sz(L1[d])) if(subt1[L1[d][i]] != subt2[L2[d][i]]) return 0;
		int k = 0;		
		loop(i,sz(L1[d])){
			int j = i;
			while(j < sz(L1[d]) && subt1[L1[d][i]] == subt1[L1[d][j]]) {
				int u = L1[d][j],v = L2[d][j];
				subt1[P1[u]].pb(k);
				subt2[P2[v]].pb(k);
				j++;
			}
			k++;
			i = j - 1;
		}
	}
	return 1;
}

int main(){
	int a,b;
	scanf("%d",&N);
	while(N--){
		scanf("%d",&n);
		loop(i,n + 1) T1[i].clear(),T2[i].clear();			
		loop(i,n - 1) {
			scanf("%d %d",&a,&b);
			T1[a].pb(b);
			T1[b].pb(a);
		}
		loop(i,n - 1) {
			scanf("%d %d",&a,&b);
			T2[a].pb(b);
			T2[b].pb(a);
		}
		vi C1,C2;
		get_centers(T1,P1,L1,C1);
		get_centers(T2,P2,L2,C2);
		if(sz(C1) != sz(C2)) puts("NO");
		else {
			bool c = 0;
			for(int c1 : C1) for (int c2 : C2) c |= check(c1,c2);
			puts(c ? "YES" : "NO");
		}
	}
	return 0;
}
