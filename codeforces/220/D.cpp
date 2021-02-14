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

const int mod = 1e9 + 7;
const vi inv{1, 1, 500000004, 333333336, 250000002, 400000003, 166666668, 142857144, 125000001, 111111112};
int add(int a, int b){
	a += b;
	if(a >= mod) a -= mod;
	if(a < 0) a += mod;
	return a;
}
int mul(int a, int b){
	return (a*(ll)b)%mod;
}

int C(int n, int k){
	if(k > n) return 0;
	k = min(k, n - k);
	assert(k < sz(inv));
	int ret = 1;
	loop(i, k) ret = mul(ret, mul(n - i, inv[i + 1]));
	return ret;
}

int W, H;

array<int, 2> split(int x){
	array<int, 2> s;
	s[0] = x/2 + 1;
	s[1] = x + 1 - s[0];
	return s;
}

array<array<int, 2>, 2> getTable(int x, int y, const array<array<int, 2>, 2> & orig) {
	array<array<int, 2>, 2> tab (orig);
	tab[0][0] --;
	if (x == 0 && y == 0) return tab;
	tab[x][y] --;
	if (x) tab[0].swap(tab[1]);
	if (y){
		loop(i, 2){
			swap(tab[i][0], tab[i][1]);
		}
	}
	tab[x][y] ++;
	return tab;
}


int f(int x, int y, const array<array<int, 2>, 2> & orig){
	auto tab = getTable(x, y, orig);
	int odd = 0;
	loop(dx1, 2) loop(dy1, 2) loop(dx2, 2) loop(dy2, 2) {
		if (abs(dx1*dy2 - dx2*dy1) & 1){
			odd = add(odd, mul(tab[dx1][dy1], tab[dx2][dy2]));
		}
	}
	odd = mul(odd, inv[2]);
	return odd;
}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	cin >> W >> H;
	auto A = split(W);
	auto B = split(H);
	array<array<int, 2>, 2> orig;
	loop(i, 2) loop(j, 2) orig[i][j] = A[i]*B[j];
	
	int N = (W + 1) * (H + 1);
	int tot = C(N, 3);
	
	int odd = 0;
	loop(i, 2) loop(j, 2){		
		int tmp = f(i, j, orig);
		tmp = mul(tmp, orig[i][j]);
		odd = add(odd, tmp); 
	}
	odd = mul(odd, inv[3]);
	
	int col = 0;
	for(int dx = 1; dx <= W; dx++)
		for(int dy = 1; dy <= H; dy++){
			int tmp = mul(mul(W - dx + 1, H - dy + 1), gcd(dx, dy) - 1);
			col = add(col, tmp);
		}
	col = mul(col, 2);
	col = add(col, mul(W + 1, C(H + 1, 3)));
	col = add(col, mul(H + 1, C(W + 1, 3)));
	
	
	cerr << tot << " " << odd << " " << col << endl;
	
	tot = add(tot, -odd);
	tot = add(tot, -col);
	
	tot = mul(tot, 6);
	cout << tot << endl;
		
	return 0;
}
