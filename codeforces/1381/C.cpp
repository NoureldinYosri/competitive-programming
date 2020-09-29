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

const int MAXN = 100*1000 + 10;
int n, x, y;
int A[MAXN], B[MAXN];

map<int, vi> IDX;

bool phase1(){
	static set<pi> S;
	S.clear();
	for(auto & p : IDX) S.emplace(sz(p.second), p.first);
	for(; x; x--){
		if(S.empty()) return 0;
		auto [c, v] = *S.rbegin();
		S.erase(*S.rbegin());
		A[IDX[v].back()] = v;
		IDX[v].pop_back();
		c--;
		if(c) S.emplace(c, v);
	}
	return 1;
}

bool phase2(){
	static vi I;
	static vp aux;
	I.clear();
	aux.clear();
	for(auto & p : IDX){
		if(!p.second.empty())
			aux.emplace_back(sz(p.second), p.first);
	}
	sort(all(aux));
	reverse(all(aux));
	for(auto [c, v] : aux){
		for(int i : IDX[v])
			I.pb(i);
	}
	vi V{all(I)};
	rotate(I.begin(), I.begin() + sz(I) - aux[0].first, I.end());
/*	loop(i, sz(I)){
		cerr << I[i] << " " << B[I[i]] << " " << B[V[i]] << endl;
	}
*/	loop(j, y){
		int i = sz(I) - j - 1;
		A[I[i]] = B[V[i]];
	}
	return 1;
}

bool phase3(){
	set<int> S{B, B+n};
	int v = 1;
	while(S.count(v)) v++;
	loop(i, n) if(A[i] == -1) A[i] = v;
	return 1;
}

bool solve(){
	if(y < x) return 0;
	int ix = x, iy = y;
	y -= x;
	IDX.clear();
	loop(i, n) IDX[B[i]].pb(i);
	fill(A, A + n, -1);
	if(!phase1() || !phase2() || !phase3())
		return 0;
	int X = 0, Y = 0;
	multiset<int> MS;
	loop(i, n) {
		X += A[i] == B[i];
		MS.insert(A[i]);
	}
	loop(i, n){
		auto ptr = MS.find(B[i]);
		if(ptr != MS.end()){
			MS.erase(ptr);
			Y++;
		}
	}
//	cerr << pi(ix, iy) << " " << pi(X, Y) << endl;
	return ix == X && iy == Y;
}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	int T; scanf("%d", &T);
	while(T--){
		scanf("%d %d %d", &n, &x, &y);
		loop(i, n) scanf("%d", B + i);
		if(solve()){
			puts("YES");
			loop(i, n) printf("%d ", A[i]);
			puts("");
		} else {
			puts("NO");
		}
	}
	return 0;
}
