#ifdef ACTIVE
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
#define tc() int T; scanf("%d",&T); for(int t = 1;t <= T;t++)
using namespace std;

const int MAX = 100*1000 + 10;
vi G[MAX];
int A[MAX];
int ord[MAX],n,m;



void solve(int s) {
	set<int> S,vis;
	loop(i,s) {
		for(int v : G[A[i]])
			S.insert(v);
	}
	loop(i,s) S.erase(A[i]),vis.insert(A[i]);
	while(s < n) {
		assert(!S.empty());
		int u = *S.begin();
		S.erase(S.begin());
		A[s++] = u;
		vis.insert(u);
		for(int v : G[u])
			if(!vis.count(v))
				S.insert(v);
	}
	loop(i,n) printf("%d%c",A[i]," \n"[i==n-1]);
}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	scanf("%d %d",&n,&m);
	loop(e,m) {
		int a,b; scanf("%d %d",&a,&b);
		G[a].push_back(b);
		G[b].push_back(a);
	}
	loop(i,n){
		scanf("%d",A + i);
		ord[A[i]] = i;
	}
	set<int> aux,vis;
	vi change(n,-1);
	loop(i,n) {
		int u = A[i];
		auto ptr = aux.upper_bound(u);
		if(ptr != aux.end())
			change[i] = *ptr;
		vis.insert(u);
		aux.erase(u);
		for(int v : G[u])
			if(!vis.count(v))
				aux.insert(v);
	}
	for(int i = n-1;i;i--) {
		if(change[i] != -1) {
			A[i] = change[i];
			solve(i+1);
			return 0;
		}
	}

	if(A[0] < n) {
		A[0]++;
		solve(1);
		return 0;
	}
	puts("-1");
	return 0;
}
#endif
