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


pi bf(int x, int y, int n){
	x--, y--;
	vi A(n);
	loop(i, n) A[i] = i;
	int mn = INT_MAX, mx = INT_MIN;
	do{
		vi B(n);
		loop(i, n) B[i] = i;
		if(A[x]) continue;
		do{
			if(B[y]) continue;
			vi score(n, 0);
			loop(i, n) score[A[i]] += i;
			loop(i, n) score[B[i]] += i;
			int v = score[0];
			int h = 0;
			loop(i, n) h += score[i] <= v;
			mn = min(mn, h);
			mx = max(mx, h);
		}while(next_permutation(all(B)));
	}while(next_permutation(all(A)));
	return pi(mn, mx);
}

int good(int x, int y, int n){
	if(x > y) swap(x, y);
	return min(n - min(n-x + n-y, n) + 1, n);
}
int bad(int x, int y, int n){
	if(x > y) swap(x, y);
	return min(x+y-1, n);
}

void test(){
	int n = rand()%5 + 1;
	int x = rand()%n + 1;
	int y = rand()%n + 1;
	pi out (good(x, y, n), bad(x, y, n));
	pi correct = bf(x, y, n);
	if(out != correct){
		cerr << "failed on " << x << " " << y << " " << n << endl;
		cerr << out << " vs " << correct << endl;
		exit(0);
	}
}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
/*	srand(time(0));
	loop(i, 100) {
		test();
		cerr << "case " << i+1 << endl;
	}
	cerr << "passed :)" << endl;
*/	int T; scanf("%d", &T);
	while(T--){
		int n, x, y; scanf("%d %d %d", &n, &x, &y);

		printf("%d %d\n", good(x, y, n), bad(x, y, n));	
	}
	
	return 0;
}
