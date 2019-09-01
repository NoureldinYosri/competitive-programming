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


bool bf(int n) {
	vi V;
	loop(i,2*n) V.push_back(i+1);
	do{
		int a = INT_MAX,b = INT_MIN;
		loop(i,2*n) {
			int s = 0;
			loop(j,n) s += V[(i + j)%sz(V)];
			a = min(a,s);
			b = max(b,s);
		}
		if(abs(b-a) <= 1) {
			print(V,int);
			return 1;
		}
	}while(next_permutation(all(V)));
	return 0;
}


int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	int n; cin >> n;
	if(n%2 == 0) puts("NO");
	else {
		puts("YES");
		vi V(2*n);
		for(int i = 0;i < n;i++) {
			int a = i+1,b = a + 1;
			if(i%2) a = 2*n-i+1,b = a - 1;
			V[i] = a;
			V[i+n] = b;
		}
		loop(i,sz(V)) printf("%d%c",V[i]," \n"[i==sz(V)-1]);
	}
	return 0;
}
#endif
