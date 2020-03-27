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

int A[1 << 20], n;
int B[1 << 20], m;
int P;
int cand[2 << 20];

int add(int a, int b){
	a += b;
	if(a >= P) a -= P;
	return a;
}
int mul(int a, int b){
	return (a*(ll)b)%P;
}

bool done[2 << 20];

bool check(int k){
	done[k] = 1;
	int v = 0;
	for(int x = max(k-(m-1), 0), L = min(k, n-1); x <= L; x++) {
		int y = k - x;
		if(y < m) v = add(v, mul(A[x], B[y]));
	}
	return v;
}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	scanf("%d %d %d", &n, &m, &P);
	loop(i, n) {
		scanf("%d", A + i);
		A[i] %= P;
	}
	loop(i, m) {
		scanf("%d", B + i);
		B[i] %= P;
	}
	
	while(n && !A[n-1]) n--;
	while(m && !B[m-1]) m--;
	


	
	for(int k = n+m-1; ; k--){
		if(check(k)){
			printf("%d\n", k);
			return 0;
		}
	}
	
	
	return 0;
}
