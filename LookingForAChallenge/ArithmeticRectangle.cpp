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

const int MAX = 3 << 10;
int n, m;
int A[MAX][MAX];
int B[MAX][MAX];
int C[MAX][MAX];

int get_H(){
	loop(i, m){
		loop(j, n){
			if(j < 2) B[i][j] = j + 1;
			else {
				int d1 = A[i][j] - A[i][j-1];
				int d2 = A[i][j-1] - A[i][j-2];
				if(d1 == d2) B[i][j] = B[i][j-1] + 1;
				else B[i][j] = 2;
			}
		}
	}
	int ret = 0;
	loop(i, m) loop(j, n) ret = max(ret, B[i][j]);
	loop(i, m-1) loop(j, n) ret = max(ret, 2*min(B[i][j], B[i+1][j]));
	return ret;
}
int get_V(){
	loop(j, n) loop(i, m) {	
		if(i <= 1) B[i][j] = i+1;
		else {
			int d1 = A[i][j] - A[i-1][j];
			int d2 = A[i-1][j] - A[i-2][j];
			if(d1 == d2) B[i][j] = B[i-1][j] + 1;
			else B[i][j] = 2;			
		}
	}
	int ret = 0;
	loop(i, m) loop(j, n) ret = max(ret, B[i][j]);
	loop(i, m) loop(j, n-1) ret = max(ret, 2*min(B[i][j], B[i][j+1]));
	return ret;
}


bool is_good(int xc, int yc){
	for(int dx = -1; dx <= 1; dx++){
		int x = xc + dx;
		int a = A[x][yc-1], b = A[x][yc], c = A[x][yc+1];
		if(b-a != c-b) return 0;
	}
	for(int dy = -1; dy <= 1; dy++){
		int y = yc + dy;
		int a = A[xc-1][y], b = A[xc][y], c = A[xc+1][y];
		if(b-a != c-b) return 0; 
	}
	return 1;
}

int hist(int *H){
	static int L[MAX], R[MAX];
	static vi ST;
	ST.clear();
	loop(i, m){
		while(!ST.empty() && H[i] <= H[ST.back()]) ST.pop_back();
		L[i] = ST.empty() ? -1 : ST.back();
		ST.pb(i);
	}
	ST.clear();
	for(int i = m-1; i >= 0;i--){
		while(!ST.empty() && H[i] <= H[ST.back()]) ST.pop_back();
		R[i] = ST.empty() ? m : ST.back();
		ST.pb(i);		
	}
	int ret = 0;
	loop(i, m) if(H[i]) ret = max(ret, (H[i] + 2) * (R[i] - L[i] + 1));
	return ret;
}

int big(){
	loop(i, m) loop(j, n) B[i][j] = 0;
	int ret = 0;
	for(int i = 1; i < m;i ++){
		for(int j = 1; j < n; j++){
			B[i][j] = is_good(i, j);
			if(B[i][j])	B[i][j] += B[i-1][j];
		}
		ret = max(ret, hist(B[i]));
	}
	return ret;
}


int solve(){
	int ret = max(get_H(), get_V());

	ret = max(ret, big());
	return ret;
}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	int T; scanf("%d", &T);
	while(T--){
		scanf("%d %d", &m, &n);
		loop(i, m) loop(j, n) scanf("%d", &A[i][j]);
		get_H();
		get_V();
		printf("%d\n", solve());
	}
	return 0;
}
