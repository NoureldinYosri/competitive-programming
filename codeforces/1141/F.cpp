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


map<int, vector<pi>> M;
int n;
int A[2000];

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	scanf("%d", &n);
	loop(i, n) scanf("%d", A + i);
	for(int j = 0;j < n; j++){
		for(int i = j, s = 0; i >= 0; i--){
			s += A[i];
			M[s].emplace_back(j, i);
		}
	}
	vector<pi> ans, aux;
	for(auto & [_, V] : M){
		aux.clear();
		
		int E = -1;
		for(auto [e, s] : V){
			if(s <= E) continue;
			E = e;
			aux.emplace_back(s, e);
		}
		if(sz(aux) > sz(ans)) ans = aux;
	}
	printf("%d\n", sz(ans));
	for(auto [s, e] : ans) 
		printf("%d %d\n", s+1, e+1);
	return 0;
}
