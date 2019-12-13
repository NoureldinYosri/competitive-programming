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
 
const int MAX = 1 << 20;
int A[MAX],n;
int P[MAX],m;
 
void def(){
	puts("0 0 0");
}
 
void solve(){
	n = 0;
	int lim = m/2;
	for(int i = 0;i < m;){
		int j = i;
		while(j < m && P[i] == P[j]) j++;
		A[n++] = j - i;
		i = j;
	}
	int g = A[0],b = 0,s = 0;
	int i = 1;
	while(i < n && s <= g)
		s += A[i++];
	while(i < n && b <= g)
		b += A[i++];
	while(i < n && g+s+b+A[i] <= lim)
		b += A[i++];
		
	if(g+s+b > lim) return def();
	if(g==0 || b==0 || s==0) return def();
	if(g >= b || g >= s) return def();
	assert(i < n);
	printf("%d %d %d\n",g,s,b);
}
 
int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	int T; scanf("%d",&T);
	while(T--){
		scanf("%d",&m);
		loop(i,m) scanf("%d",P + i);
		solve();
	}
	return 0;
}
