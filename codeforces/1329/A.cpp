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

const int MAX = 100*1000 + 10;
int n, m;
int L[MAX];
int P[MAX];
int A[MAX];
int ord[MAX];


int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	scanf("%d %d", &n, &m);
	loop(i, m)  scanf("%d", L + i);
	
	int N = n;
	loop(i, m){
		if(L[i] > N) {
			puts("-1");
			return 0;
		}
		P[i] = N - L[i] + 1;
		N--;
	}
	
//	prArr(P, m, int);
	if(N >= L[m-1]){
		int e = 0;
		for(int i = m-1; i >= 0;i--){
			if(e + 1 >= P[i]) {
				e = n;
				break;
			}
			P[i] = e+1;
			e = P[i] + L[i] - 1;
		}
		if(e != n){
			puts("-1");
			return 0;
		}
	}
	
	loop(i, m) printf("%d\n", P[i]);
	
	return 0;
}
