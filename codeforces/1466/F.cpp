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

const int mod = 1e9 + 7;
int n, m;
vi ans;
int Rank;


int id[1 << 20];
vi X[1 << 20];

int find(int a){
	if(a == -1) return -1;
	return id[a] = (a == id[a]) ? a : find(id[a]);
}

bool done[1 << 20];

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	scanf("%d %d", &n, &m);
	loop(i, n){
		int z; scanf("%d", &z);
		loop(j, z){
			int x; scanf("%d", &x);
			x--;
			X[i].push_back(x);
		}
	}
	iota(id, id + m, 0);
	vi aux;
	loop(p, n){
		if(sz(X[p]) == 1){
			int i = X[p][0];
			i = find(i);
			if(i == -1) continue;
			if(!done[i]){
				ans.push_back(p);
				done[i] = true;
				Rank++;
				id[i] = -1;
			}
		} else {
			int i = X[p][0], j = X[p][1];
			i = find(i);
			j = find(j);
			aux.clear();
			if(i != -1 && !done[i]) aux.push_back(i);
			if(j != -1
			Rank++;
			ans.push_back(p);
			done[i] = true;
			if(!done[j]){
				id[i] = j;
			} else {
				id[i] = -1;
			}
		}
	}
	int ans = 1;
	loop(i, Rank) {
		ans += ans;
		if(ans >= mod) ans -= mod;
	}
	printf("%d %d\n", ans, sz(::ans));
	sort(all(::ans));
	for(int x : ::ans) printf("%d ", x + 1);
	puts("");
	return 0;
}
