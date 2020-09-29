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


vi id, W;
vector<list<int>> who;
int n, m;
vi color;

void init(){
	id.resize(n);
	iota(all(id), 0);
	
	W.resize(n);
	fill(all(W), 1);
	
	who.resize(n);
	loop(i, n) who[i].pb(i);
	
	color.resize(n, 0);
}

int find(int a){
	return id[a] = (a == id[a]) ? a : find(id[a]);
}

void join(int x, int y){
	int a = find(x), b = find(y);
	if(a == b) return;
	if(W[a] < W[b]) swap(a, b);
	id[b] = a;
	W[a] += W[b];
	if(color[x] == color[y]){
		for(int v : who[b])
			color[v] ^= 1;
	}
	who[a].splice(who[a].end(), who[b]);
}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	scanf("%d %d", &n, &m);
	init();
	int s = 0;
	loop(e, m){
		int t, a, b; scanf("%d %d %d", &t, &a, &b);
		a = (a+s)%n;
		b = (b+s)%n;
		if(t == 0){
			join(a, b);
		} else {
			s += 1 - (color[a] ^ color[b]);
			puts((color[a]^color[b]) ? "NO" : "YES");
		}
	}
	return 0;
}
