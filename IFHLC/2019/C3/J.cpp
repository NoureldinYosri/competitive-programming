#ifdef ACTIVE
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
#define tc() int T; scanf("%d",&T); for(int t = 1;t <= T;t++)
using namespace std;


char str[1 << 20];
int n;
int G[1 << 20];

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	tc(){
		scanf("%d %s",&n,str);
		ll sum = n*(n + 1LL)/2;
		if(sum%2 != 0) strcpy(str,"-1");
		else {
			int s = 1,e = n - (n%4 == 3);
			if(n%4 == 3) G[n] = 1;
			for(int k = 0;s < e;k ^= 1) {
				G[s] = G[e] = k;
				s++,e--;
			}
			loop(i,n) {
				int d = str[i] - '0',pos = i + 1;
				d *= 2;
				d += G[pos] + 1;
				str[i] = d + '0';
			}
		}
		puts(str);
	}
	return 0;
}
#endif
