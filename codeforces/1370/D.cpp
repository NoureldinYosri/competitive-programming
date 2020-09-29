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

int n, m;
int A[1 << 20];

bool check(int x, int c, int a, int b){
	int turn = c;
	for(int i = 0; i < n; i++){
		if(turn == 0){
			if(A[i] <= x && a) {
				turn ^= 1;
				a--;
			}
		} else {
			if(b) {
				b--;
				turn ^= 1;
			}
		}
	} 
	return a==0 && b==0;
}

bool can(int x){
	return check(x, 0, (m + 1)/2, m/2) || check(x, 1, m/2, (m+1)/2);
}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	scanf("%d %d", &n, &m);
	loop(i, n) scanf("%d", A + i);
	vi S{A,A + n};
	sort(all(S));
	S.resize(unique(all(S)) - S.begin());
	int s = 0, e = sz(S) - 1;
	while(s < e) {
		int m = (s + e) >> 1;
		if(can(S[m])) e = m;
		else s = m+1;
	}
	cout << S[s] << endl;
	return 0;
}
