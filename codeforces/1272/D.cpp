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
int suff[1 << 20];


int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	scanf("%d",&n);
	loop(i,n) scanf("%d",A + i);
	A[n] = INT_MIN;
	int ans = 1;
	for(int i = n-1;i >= 0;i--)
		ans = max(ans,suff[i] = 1 + (A[i] < A[i+1])*suff[i+1]);
	int pref = 0;
	int prv = INT_MAX;
	loop(i,n){
		ans = max(ans,(pref + suff[i+1]) * (prv < A[i+1]));
		int v = A[i];
		pref = 1 + (prv < v)*pref;
		prv = v;
	}
	cout << ans << endl;
	return 0;
}
