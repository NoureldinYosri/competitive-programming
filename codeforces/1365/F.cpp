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

vi A, B;
int n;

void work(){
	scanf("%d", &n);
	A.resize(n);
	B.resize(n);
	for(int & x : A) scanf("%d", &x);
	for(int & x : B) scanf("%d", &x);
	
	int m = n >> 1;
	if(n & 1){
		if(A[m] != B[m]) {
			puts("No");
			return ;
		}
	}
	
	map<pi, int> M;
	loop(i, m){
		pi x(A[i], A[n-1-i]);
		if(x.first > x.second) swap(x.first, x.second);
		M[x]++;
	}
	
	loop(i, m){
		pi y(B[i], B[n-1-i]);
		if(y.first > y.second) swap(y.first, y.second);
		M[y]--;
		if(M[y] < 0) {
			puts("No");
			return ;
		}
	}	
	puts("Yes");
}


int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	int T; scanf("%d", &T);
	while(T--) work();
	return 0;
}
