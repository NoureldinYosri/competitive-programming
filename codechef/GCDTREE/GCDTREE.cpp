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

vi L[1 << 20],G[1 << 20];
map<int,int> Z[1 << 20];
int P[1 << 20],D[1 << 20],N,r;
int A[1 << 20];

void bfs(){
	queue<int> q;
	fill(P,P + N,-2);	
	q.push(0);
	P[0] = -1;
	D[0] = 0;
	r = 0;
	while(!q.empty()){
		int u = q.front(); q.pop();
		L[D[u]].pb(u);
		for(int v : G[u])
			if(v != P[u]){
				q.push(v);
				P[v] = u;
				r = D[v] = D[u] + 1;
			}
	}
}

long long solve(){
	
	for(;r;r--){
		for(int u : G[r]){
			for(auto p : Z[u])
		}
	}
}


int main(){
	
	return 0;
}