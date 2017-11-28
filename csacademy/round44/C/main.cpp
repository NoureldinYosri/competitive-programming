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
stack<int> ST;
int n,m;
int P[MAX];
int ctr[MAX];

int main(){
	#ifdef HOME
		freopen("in.in", "r", stdin);
	#endif
	scanf("%d %d",&n,&m);
	range(i,1,n) scanf("%d",P + i);
	loop(i,m){
		int a,b; scanf("%d %d",&a,&b);
		G[a].pb(b);
		G[b].pb(a);
	}
	range(i,1,n) sort(all(G[i]));
	G[0].pb(P[1]);
	G[P[1]].pb(0);
	sort(all(G[P[1]]));
	ST.push(0);
	for(int i = 1;i <= n;i++){
		if(ST.empty()){
			puts("0");
			return 0;
		}
		int p = ST.top(),u = P[i];
		//cerr << p << " " << u << endl;
		//cerr << binary_search(all(G[p]),u) << endl;
		if(binary_search(all(G[p]),u)) {
			for(int v : G[u]) ctr[v]++;
			ST.push(u);
			while(!ST.empty() && ctr[ST.top()] == sz(G[ST.top()]))
				ST.pop();
		}
		else {
			puts("0");
			return 0;
		}
	}
	puts("1");
	return 0;
}
