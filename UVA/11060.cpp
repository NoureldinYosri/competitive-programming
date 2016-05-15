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

int ord[1000],V[1000],t;
vi G[1000];

void dfs(int u){
	V[u] = 1;
	for(int v : G[u]) if (!V[v]) dfs(v);
	ord[t++] = u;
}

int main(){
	pre();
	int n,m,cs = 1; string s,T;
	while(cin >> n){
		t = 0;
		loop(i,n) V[i] = 0,G[i].clear();
		map<int,string> iF; map<string,int> F;
		loop(i,n){
			cin >> s;
			F[s] = i;
			iF[i] = s;
		}
		cin >> m;
		loop(i,m){
			cin >> s >> T;
			G[F[s]].pb(F[T]);
		}
		loop(i,n) sort(all(G[i]));
		loop(i,n) if(!V[i]) dfs(i);
		reverse(ord,ord + n);
		loop(k,n)
		for(int i = 1;i < n;i++){
			int j = i;
			while(j > 0){
				if(binary_search(all(G[ord[j - 1]]),ord[j])) break;
				if(ord[j - 1] < ord[j]) break;
				swap(ord[j - 1],ord[j]);
				--j;
  			}
		}
		cout << "Case #" << cs++ << ": Dilbert should drink beverages in this order:";
		loop(i,n) cout << " " << iF[ord[i]];
		cout << ".\n\n"; cout << flush;
	}
}

