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

int n,m;
int G[510][510];
char line[510];

int main(){
	scanf("%d %d",&n,&m);
	loop(i,m){
		int a,b;	
		scanf("%d %d",&a,&b);
		a--,b--;
		G[a][b] = G[b][a] = 1;
	}
	loop(i,n) G[i][i] = 1;
	line[n] = '\0';
	queue<pi> q;
	loop(i,n) loop(j,i) if(G[i][j] == 0) q.push(mp(i,j));
	while(!q.empty()){
		int u = q.front().xx,v = q.front().yy; q.pop();
		if(line[u] && line[v]){
			if(abs(line[u] - line[v]) <= 1){
				puts("No");
				return 0;
			} 
		}
		else if(line[u]) line[v] = (line[u] == 'a') ? 'c' : 'a';
		else if(line[v]) line[u] = (line[v] == 'a') ? 'c' : 'a';
		else{
			line[u] = 'a';
			line[v] = 'c';
		}
	}
	loop(i,n){
		if(!line[i]) line[i] = 'b';
	}
	loop(i,n) loop(j,n){
		if(G[i][j]){
			if(abs(line[i] - line[j]) == 2){
				puts("No");
				return 0;
			}
		}
		else{
			if(abs(line[i] - line[j]) <= 1){
				puts("No");
				return 0;
			}
		}
	}
	puts("Yes");
	puts(line);
	return 0;
}
