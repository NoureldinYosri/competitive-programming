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


char command[20];
vector<pair<int*, int>> hist;
int n, m;
vi id, W;
vi breakPoints;

void replace(int *ptr, int v){
	hist.emplace_back(ptr, *ptr);
	*ptr = v;
}

int find(int a){
	if(id[a] == a) return a;
	replace(&id[a], find(id[a]));
	return id[a];
}

void join(int a, int b){
	a = find(a);
	b = find(b);
	if(a == b) return;
	replace(&n, n-1);
	if(W[a] < W[b]) swap(a, b);
	replace(&id[b], a);
	replace(&W[a], W[a] + W[b]);
}


int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	scanf("%d %d", &n, &m);
	id.resize(n);
	W.resize(n);
	fill(all(W), 1);
	iota(all(id), 0);
	
	while(m--){
		scanf("%s", command);
		if(command[0] == 'p'){
			breakPoints.pb(sz(hist));
		} else if(command[0] == 'r') {
			while(sz(hist) > breakPoints.back()){
				auto [ptr, v] = hist.back(); hist.pop_back();
				*ptr = v;
			}
			breakPoints.pop_back();
			printf("%d\n", n);
		} else {
			int a, b; scanf("%d %d", &a, &b);
			a--, b--;
			join(a, b);
			printf("%d\n", n);
		}
	}
	return 0;
}
