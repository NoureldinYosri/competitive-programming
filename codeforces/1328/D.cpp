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

int A[1 << 20];
int n;
int color[1 << 20];

int solve(){
	int x = A[0];
	bool are_eq = 1;
	loop(i, n) are_eq &= A[i] == x;
	if(are_eq){
		loop(i, n) color[i] = 1;
		return 1;
	}

	int q = -1;
	loop(i, n) if(A[i] == A[(i+1)%n]) {
		q = i;
		break;
	}
	if(q != -1 || n%2 == 0){
		loop(i, n) color[i] = (i&1) + 1;
//		prArr(color, n, int);
		if(A[0] != A[n-1] && color[0] == color[n-1]){
			loop(i, q+1) color[i] = (i + 1)%2 + 1;
		}
		
		return 2;
	}
	
	
	loop(i, n) color[i] = i%3 + 1;
	
	if(A[0] != A[n-1] && color[0] == color[n-1]){
		color[0] = 3;
	}
	return 3;
}


int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	int T; scanf("%d", &T);
	while(T--){
		scanf("%d", &n);
		loop(i, n) scanf("%d", A + i);
		printf("%d\n", solve());
		loop(i, n) printf("%d%c", color[i], " \n"[i==n-1]);
	}
	return 0;
}
