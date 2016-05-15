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
#define LSOne(x) ((x) & (-(x)))
#define xx first
#define yy second
#define prp(p) cout << "(" << (p).first << " ," << (p).second << ")";
#define prArr(A,n,t)  cout << #A << ": "; copy(A,A + n,ostream_iterator<t>(cout," " )); cout << endl
using namespace std;

const int MAX = 500000;
int deg[MAX],P[MAX];
int state[MAX],V[MAX];
vi G[MAX];


int main(){
	freopen("grant.in","r",stdin);
	freopen("grant.out","w",stdout);
	int n;
	scanf("%d",&n);
	loop(i,n - 1){
		int a; 
		scanf("%d",&P[i + 1]); P[i + 1]--;		
		deg[P[i + 1]]++;
		G[P[i + 1]].pb(i + 1);
	}
	
	loop(i,n) state[i] = i > 0;
	rrep(u,n - 1){
		if(state[u]) {
			state[P[u]] = 0;
		}
		else {
			int ctr = 0;
			for(int v : G[u]) ctr += state[v];
			for(int v : G[u]){
				if(ctr <= 1) break;
				ctr -= state[v];
				state[v] = 0;
			}
		}
	}
	state[0] = 0;
	int ctr = 0;
	loop(i,n) ctr += state[i];
	printf("%d\n",ctr * 1000);
	loop(i,n)if(state[i]){
		ctr--;
		printf("%d%s",i + 1,ctr ? " " : "\n");
	}
	return 0;
}
