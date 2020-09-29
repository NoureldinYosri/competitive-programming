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

const int mod = 998244353;
int add(int a, int b){
	a += b;
	if(a >= mod) a -= mod;
	if(a < 0) a += mod;
	return a;
}
int mul(int a, int b){
	return (a*(ll)b)%mod;
}
int m, n;
deque<int> A;
vi B;
const int MAXLG = 20;
int ST[1 << MAXLG][MAXLG];
int lg[1 << MAXLG];

void init(){
	m = sz(A);
	lg[0] = -1;
	for(int i = 1; i <= m; i++)
		lg[i] = lg[i-1] + (i == LSOne(i));
	loop(i, m) ST[i][0] = A[i];
	loop(k, MAXLG-1){
		loop(i, m){
			int j = i + (1 << k);
			if(j >= m) j = i;
			ST[i][k+1] = min(ST[i][k], ST[j][k]);
		}
	}
}

int query(int s, int e){
	assert(s <= e);
	int l = lg[e-s+1];
	return min(ST[s][l], ST[e-(1<<l)+1][l]);
}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	scanf("%d %d", &m, &n);
	if(m < n){
		puts("0");
		return 0;
	}
	A.resize(m);
	B.resize(n);
	for(int & x : A) scanf("%d", &x);
	for(int & y : B) scanf("%d", &y);
	while(!A.empty() && A.front() != B[0]){
		int x = A.front(); A.pop_front();
		if(x < B[0]){
			puts("0");
			return 0;
		}
	} 
	while(!A.empty() && A.back() != B.back()){
		int x = A.back(); A.pop_back();
		if(x < B.back()){
			puts("0");
			return 0;
		}
	}
	if(sz(A) < sz(B)){
		puts("0");
		return 0;		
	}
	
	init();
	
	



	map<int, int> dp;
	int f = 0;
	for(int i = m-1; i >= 0; i--) if(binary_search(all(B), A[i])){
		int x = A[i];
		if(x == B.back()) {
			f = query(i, m-1) == x;
		}
		else {
			int y = *upper_bound(all(B), x);
			f = dp[y];
		}
		f *= query(i, m-1) == x;
		int scale = 1;
		int l = i;
		if(i && A[i-1] > x){
			int s = 0, e = i-1;
			while(s < e) {
				int m = (s + e) >> 1;
				if(query(m, i-1) > x) e = m;
				else s = m+1;
			}
			scale = i-e+1;
			l = e;
		}
		if(x != B[0] && l){
			auto ptr = lower_bound(all(B), x);
			ptr--;
			int y = *ptr;
			if(A[l-1] < y){
				scale = 0;
			} else {
				int s = 0, e = l-1;
				while(s < e){
					int m = (s + e) >> 1;
//					cerr << s << " " << l-1 << " " << query(s, l-1) << " vs " << y << endl;
					if(query(m, l-1) >= y) e = m;
					else s = m+1;
				}
//				cerr << s << " " << l-1 << " " << query(s, l-1) << endl;
				if(query(s, l-1) != y){
					scale = 0;
				}				
			}
		}
//		cerr << "@" << i << " " << x << ": " << f << " " << scale << endl;
		dp[x] = add(dp[x], mul(f, scale));
	}
	cout << f << endl;
	cerr << f << endl;
	return 0;
}
