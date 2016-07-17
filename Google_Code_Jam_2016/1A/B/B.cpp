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


struct cmp{
	int h;
public:
	cmp(int x):h(x){}
	bool operator () (const deque<int> & dq1,const deque<int> & dq2){
		deque<int> U = dq1,V = dq2;
		loop(i,h) U.pop_front(),V.pop_front();
		return U < V;
	}
};

vector<deque<int> > V;
int n,T;

bool row[50],col[50];
int Z[50][50];

void fill_row(deque<int>  v,int r,int G[50][50]){
	loop(i,n){
		if(i < r && v[0] == -1) continue;
		G[r][i] = v[i];
	}
	row[r] = v[0] != -1;
}

void fill_col(deque<int>  v,int c,int G[50][50]){
	loop(i,n) {
		if(i < c && v[0] == -1) continue;
		G[i][c] = v[i];
	}
	col[c] = v[0] != -1;
}

bool check_row(deque<int> & v,int r,int G[50][50] ){
	if(r == 0) return 1;
	loop(i,n) if(G[r - 1][i] >= v[i]) return 0;
	loop(i,r) if(v[i] != G[r][i] && G[r][i] != -1) return 0;
	return 1;
}

bool check_col(deque<int> & v,int c,int G[50][50]){
	if(c == 0) return 1;
	loop(i,n) if(G[i][c - 1] >= v[i]) return 0;
	loop(i,c) if(v[i] != G[i][c] && G[i][c] != -1) return 0;
	return 1;
}

bool solve(int i,int u,int v,int who,int which,int G[50][50]){
	cerr << i << endl;
	if(i == n || v == 2*n - 1){
		if(check_row(V[who],which,G)) fill_row(V[who],which,G);
		else if(check_col(V[who],which,G)) fill_col(V[who],which,G);
		else return 0;		
		loop(i,n) loop(j,n) Z[i][j] = G[i][j];
		return 1;
	}
	sort(all(V),cmp(i));
	print(V[u],int);
	print(V[v],int);
	cerr << endl;	
	int U[50][50],VV[50][50];
	loop(i,n)loop(j,n) U[i][j] = VV[i][j] = G[i][j];
	if(V[u][i] != V[v][i]){
		fill_row(deque<int>(n,-1),i,U);
		fill_col(deque<int>(n,-1),i,U);
		return solve(i + 1,u + 1,v + 1,u,i,U);	
	}
	else{
		if(check_row(V[u],i,U) && check_col(V[v],i,U)){
			fill_row(V[u],i,U);
			fill_col(V[v],i,U);
			if(solve(i + 1,u + 2,v + 2,who,which,U)) return 1;
			row[i] = col[i] = 0;		
		}
		if(check_col(V[u],i,VV) && check_row(V[v],i,VV)){
			fill_col(V[u],i,VV);
			fill_row(V[v],i,VV);
			if(solve(i + 1,u + 2,v + 2,who,which,VV)) return 1;		
			row[i] = col[i] = 0;		
		}
		return 0;
	}
}

int main(){
	scanf("%d",&T);
	loop(t,T){
		V.clear();
		scanf("%d",&n);
		loop(i,2*n - 1){
			V.pb(deque<int>());
			loop(j,n) {
				row[i] = col[i] = 0;
				int a;
				scanf("%d",&a);
				V.back().pb(a);
			}
		}
		if(!solve(0,0,1,2*n - 2,n - 1,Z)) cout << "Err" << endl;
		loop(i,2*n - 1) {print(V[i],int);}		
		printf("Case #%d:",t + 1);
		loop(i,n) {
			if(!row[i]){
				loop(j,n) printf(" %d",Z[i][j]);
				puts("");
			}
			else if(!col[i]) {
				loop(j,n) printf(" %d",Z[j][i]);
				puts("");
			}
		}
	}		
	return 0;
}