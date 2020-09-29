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

int m, n;
vector<list<int>> divs;
vi P, X;
vi taken;
pi A, B;
vi checked;

bool solve2(){
	int f = -1;
	int g = 0;
	loop(i, n) if(!taken[i]){
		if(f == -1) f = X[i];
		else {
			g = __gcd(g, X[i] - f);
		}
	}
	if(g == 0) {
		B.first = (f == -1) ? 1 : f;
		B.second = P[0];
		return 1;
	} else if(!divs[g].empty()){ 
		B.first = f;
		B.second = divs[g].back();
		return 1;
	} else {
		return 0;	
	}
}

bool solve1(){
	for(int i = 1; i < n && i <= 3; i++){
		int diff = X[i] - X[0];
		for(int d : divs[diff]) if(!checked[d]) {
			checked[d] = 1;
			A = pi(X[0], d);
			for(int j = 1; j < n;j ++){
				if((X[j]-X[0])%d == 0){
					taken[j]++;
				}
			}
			if(solve2()) return 1;
			for(int j = 1; j < n;j ++){
				if((X[j]-X[0])%d == 0){
					taken[j]--;
				}
			}
		}
	}
	return 0;
}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	scanf("%d %d", &m, &n);
	P.resize(m);
	X.resize(n);
	taken.resize(n, 0);
	for(int & p : P) scanf("%d", &p);
	for(int & x : X) scanf("%d", &x);
	
	divs.resize(X.back() - X[0] + 1);
	checked.resize(P.back() + 1, 0);
	for(int p : P)
		for(int x = p; x < sz(divs); x += p)
			divs[x].pb(p);
	
	taken[0] = 1;
	if(solve1()) {
		puts("YES");
		printf("%d %d\n", A.first, A.second);
		printf("%d %d\n", B.first, B.second);		
	} else {
		puts("NO");
	}
	
	return 0;
}
