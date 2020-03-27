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


char A[1 << 20], B[1 << 20];
int n;
char txt[1 << 20];

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	int T; scanf("%d", &T);
	while(T--){
		scanf("%d %s", &n, txt);
		int are_equal = 1;
		loop(i, n){
			if(txt[i] == '0') A[i] = B[i] = '0';
			else if(txt[i] == '2') {
				if(are_equal) A[i] = B[i] = '1';
				else {
					A[i] = '0';
					B[i] = '2';
				}
			}
			else if(are_equal){
				A[i] = '1';
				B[i] = '0';
				are_equal = 0;
			}
			else {
				A[i] = '0';
				B[i] = '1';
			}
		}
		A[n] = B[n] = 0;
		puts(A);
		puts(B);
	}
	return 0;
}
