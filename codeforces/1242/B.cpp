#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define all(A) A.begin(),A.end()
#define pb push_back
#define mp make_pair
#define sz(A) ((int)A.size())
typedef std::vector<int> vi;
typedef std::pair<int,int> pi;
typedef std::vector<pi> vp;
typedef long long ll;
#define popcnt(x) __builtin_popcount(x)
#define LSOne(x) ((x) & (-(x)))
#define print(A,t) cerr << #A << ": "; copy(all(A),ostream_iterator<t>(cerr," " )); cerr << endl
#define prArr(A,n,t)  cerr << #A << ": "; copy(A,A + n,ostream_iterator<t>(cerr," " )); cerr << endl
#define PRESTDIO() cin.tie(0),cerr.tie(0),ios_base::sync_with_stdio(0)
#define what_is(x) cerr << #x << " is " << x << endl
#define bit_lg(x) (assert(x > 0),__builtin_ffsll(x) - 1)
const double PI = acos(-1);
template<class A,class B>
std::ostream& operator << (std::ostream& st,const std::pair<A,B> p) {
	st << "(" << p.first << ", " << p.second << ")";
	return st;
}
using namespace std;

vi G[1 << 20];
int n, m;
set<int> S;

queue<int> q;
vi aux;
void bfs(int u){
	S.erase(u);
	q.push(u);
	while(!q.empty()){
		int u = q.front(); q.pop();
		aux.clear();
		for(int v : S) if(!binary_search(all(G[u]), v)) aux.push_back(v);
		for(int v : aux){
			S.erase(v);
			q.push(v);
		}
	}
}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	scanf("%d %d", &n, &m);
	loop(e, m) {
		int a, b; scanf("%d %d", &a, &b);
		G[a].push_back(b);
		G[b].push_back(a);
	}
	for(int u = 1; u <= n; u++){
		sort(all(G[u]));
		S.insert(u);
	}
	int ans = 0;
	while(!S.empty()){
		ans++;
		bfs(*S.begin());
	}
	cout << ans - 1 << endl;
	return 0;
}
