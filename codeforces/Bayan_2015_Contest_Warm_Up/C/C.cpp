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

char G[1000][1010];
int accounted_for[1000][1010];
int m,n;
void paint(int x,int y,int v){
	if(x == m || y == n) return;
	accounted_for[x][y] = v;
}

bool get(int x,int y){
	if(x == m || y == n) return 1;
	return G[x][y] == 'X';
}

int main(){
	scanf("%d %d",&m,&n);
	loop(i,m) scanf("%s",G[i]);
	loop(i,m){
		loop(j,n){
			if(get(i,j) && get(i,j + 1) && get(i + 1,j + 1)){
				paint(i,j,1);
				paint(i,j + 1,1);
				paint(i + 1,j + 1,1);	
			}
		}
	}
	loop(i,m) loop(j,n) if(G[i][j] == 'X' && !accounted_for[i][j]){
		puts("-1");
		return 0;
	} 
	int ctr = 1;
	loop(i,m - 1) loop(j,n - 1) {
		if(G[i][j] == 'X' && accounted_for[i][j] == 1){
			paint(i,j,++ctr);
			paint(i,j + 1,ctr);
			paint(i + 1,j + 1,ctr);
		}
	}
	printf("%d\n",ctr - 1);
	return 0;
}
