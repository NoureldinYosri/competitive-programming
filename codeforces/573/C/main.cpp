#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define range(i,a,b) for(int i = (a);i <= (b);i++)
#define all(A) A.begin(),A.end()
#define pb push_back
#define mp make_pair
#define sz(A) ((int)A.size())
#define vi vector<int>
#define vl vector<long long>
#define vd vector<double>
#define vp vector<pair<int,int> >
#define ll long long
#define pi pair<int,int>
#define popcnt(x) __builtin_popcountll(x)
#define LSOne(x) ((x) & (-(x)))
#define xx first
#define yy second
#define PQ priority_queue
#define print(A,t) cerr << #A << ": "; copy(all(A),ostream_iterator<t>(cerr," " )); cerr << endl
#define prp(p) cerr << "(" << (p).first << " ," << (p).second << ")";
#define prArr(A,n,t)  cerr << #A << ": "; copy(A,A + n,ostream_iterator<t>(cerr," " )); cerr << endl
#define PRESTDIO() cin.tie(0),cerr.tie(0),ios_base::sync_with_stdio(0)
#define what_is(x) cerr << #x << " is " << x << endl
#define bit_lg(x) (assert(x > 0),__builtin_ffsll(x) - 1)
const double PI = acos(-1);
using namespace std;

const int MAX = 100*1000 + 10;
vi G[MAX];
int dp[MAX][2][2][2],n;

int solve(int u,int p,bool up,bool left,bool right){
	int & ret = dp[u][up][left][right];
	if(ret != -1) return ret;
	ret = 0;
	if((sz(G[u]) == 1) && p) ret = 1; // leafs
	vi children;
	for(int v : G[u]) if(v != p){
		loop(i,2) loop(j,2) loop(k,2) solve(v,u,i,j,k);
		children.pb(v);
	}
	if(up) {

	}
	else if(left && right){

	}
	else if(left){

	}
	else if(right) {

	}
	else {
		int deg = sz(children);
		if(deg > 2) ret = 0;
		else if(deg == 0) ret = 1;
		else if(deg == 1){
			ret = solve(children[0],u,0,0,0);
		}
		else {
			ret = solve(children[0],u,0,0,0);
			ret &= solve(children[1],u,0,0,0);
		}
	}
	return ret;
}

int main(){
	#ifdef HOME
		freopen("in.in", "r", stdin);
	#endif
	scanf("%d",&n);
	loop(i,n-1) {
		int a,b;scanf("%d %d",&a,&b);
		G[a].pb(b);
		G[b].pb(a);
	}
	int root = 1;
	range(i,1,n) if(sz(G[i]) == 1) root = i;
	puts(solve(root,0,1,1,1) ? "Yes" : "No");

	return 0;
}
