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


const int MAXN = 200*1000 + 10;
int A[MAXN << 1], B[MAXN << 1], n, L;
int F[MAXN << 1];
vi I[MAXN << 1], R[MAXN << 1];
int big[MAXN << 1];
bool takenA[MAXN], takenB[MAXN];

int get_pos(int x){
	if(x >= L) x -= L;
	if(x < 0) x += L;
	return x;
}

bool can(int D){
	loop(i, 2*n){
		int x = get_pos(B[i] - D);
		if(x < 0) continue;
		int f = lower_bound(A, A + 2*n, x) - A;
		int lst = upper_bound(A, A + 2*n, B[i] + D) - A;
		if(f == lst) continue;
		I[lst-1].pb(i);
		R[f].pb(i);		
	}
	loop(i, n) takenA[i] = takenB[i] = 0;
	multiset<int> MS; 
	for(int i = 2*n-1; i >= 0; i--){
		for(int x : I[i]) MS.insert(x);
		if(!MS.empty()) big[i] = *MS.rbegin();
		else big[i] = -1;
		for(int x : R[i]) MS.erase(MS.find(x));
	}
	
	return 1;
}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	scanf("%d %d", &n, &L);
	loop(i, n) scanf("%d", A + i);
	loop(i, n) scanf("%d", B + i);
	sort(A, A + n);
	sort(B, B + n);
	loop(i, n){
		A[i + n] = A[i] + L;
		B[i + n] = B[i] + L;
	}
	
	
	int s = 0, e = L >> 1;
	
	while(s < e){
		int m = (s + e) >> 1;
		if(can(m)) e = m;
		else s = m+1;
	}
	
	printf("%d\n", s);
		
	
	return 0;
}
