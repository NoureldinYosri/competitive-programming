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

#define WIN 2
#define LOSE 1
#define DRAW 0

int n;
int A[1 << 20];
char output[3][10] = {"DRAW", "LOSE", "WIN"};

int solve(){
	int x = 0;
	loop(i, n) x ^= A[i];
	if(x == 0) return DRAW;
	
	int b = 30;
	while(!((x >> b) & 1)) b--;
	int ones = 0;
	loop(i, n) ones += (A[i] >> b) & 1;
	return (ones%4 == 3 && (n - ones)%2 == 0) ? LOSE : WIN;
}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	int T; scanf("%d", &T);
	while(T--){
		scanf("%d", &n);
		loop(i, n) scanf("%d", A + i);
		printf("%s\n", output[solve()]);
	}
	return 0;
}
