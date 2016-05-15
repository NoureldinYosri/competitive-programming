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

vi G[100];
int V[100];
pi e,E[5050];
int n,m,a,b;

bool dfs(int u,int p){
	V[u] = 1;
	for(int v : G[u]){
		if(u == e.first && v == e.second) continue;
		if(v == e.first && u == e.second) continue;
		if(V[v]){
			if(v != p) return 1; 
		}
		else{
			if(dfs(v,u)) return 1;
		}
	}
	return 0;
}

bool is_tree(){
	fill(V,V + n,0);
	if(dfs(0,-1)) return 0;
	loop(i,n) if(!V[i]) return 0;
	return 1;
}

int main(){
	pre();
	cin >> n >> m;
	loop(i,m){
		cin >> a >> b; --a,--b;
		G[a].pb(b);
		G[b].pb(a);
		E[i] = mp(a,b);	
	}
	loop(i,m){
		e = E[i];
		if(is_tree()){
			cout << "FHTAGN!" << endl;
			return 0;
		}
	}
	cout << "NO" << endl;
	return 0;
}

