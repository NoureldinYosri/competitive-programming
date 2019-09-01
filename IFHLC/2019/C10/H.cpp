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
int n,m;
vi T[2][MAX];
int Len[MAX];


int getDiameter(int u,int p,int & D,vi *T) {
	int mx = 0,mx2 = 0;
	for(int v : T[u]) {
		if(v == p) continue;
		int len = getDiameter(v,u,D,T) + 1;
		mx2 = max(mx2,len);
		if(mx < mx2) swap(mx,mx2);
	}
	D = max(D,mx + mx2);
	return Len[u] = mx;
}

void readTree(int & n,vi *T){
	scanf("%d",&n);
	loop(e,n-1) {
		int a,b; scanf("%d %d",&a,&b);
		T[a].push_back(b);
		T[b].push_back(a);
	}
}


int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	readTree(n,T[0]);
	readTree(m,T[1]);
	int D1 = 0;
	getDiameter(1,0,D1,T[0]);
	int D2 = 0;
	getDiameter(1,0,D2,T[1]);
	D2 = (D2 + 1)/2;
	puts((D1 > D2) ? "GGEZ" : "FF");
	return 0;
}
#endif
