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

const int MAX = 1 << 20;
vi G[MAX];
int n,m;
int color[MAX];

void step1(){
	for(int v : G[1])
		color[v] = 0;
}


void step2(){
	for(int u = 1;u <= n;u++)
		if(!color[u]) {
			for(int v : G[u])
				if(!color[v])
					color[v] = 3;
			break;
		}
	for(int u = 1;u <= n;u++)
		if(!color[u])
			color[u] = 2;
}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	scanf("%d %d",&n,&m);
	loop(e,m){
		int a,b; scanf("%d %d",&a,&b);
		G[a].push_back(b);
		G[b].push_back(a);
	}
	for(int i = 1;i <= n;i++) color[i] = 1;
	step1();
	for(int u = 1;u <= n;u++) if(color[u] == 1) {
		for(int v : G[u]) if(color[v] == 1) {
			puts("-1");
			return 0;
		}
	}

	step2();

	ll cnt[4] = {0,0,0,0};
	for(int u = 1;u <= n;u++){
		for(int v : G[u])
			if(color[u] == color[v]) {
				puts("-1");
				return 0;
			}
		cnt[color[u]]++;
	}

	ll a = cnt[1],b = cnt[2],c = cnt[3];
	if(!a || !b || !c) {
		puts("-1");
		return 0;
	}
	ll needed = a*b + b*c + a*c;
	if(needed != m) {
		puts("-1");
		return 0;
	}
	loop(i,n) printf("%d%c",color[i+1]," \n"[i==n-1]);
	return 0;
}
#endif
