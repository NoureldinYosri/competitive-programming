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

const int MAXN = 100*1000 + 10;
int vis[MAXN],n;
int P[3],V[3];

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	cin >> n;
	loop(i,3) cin >> V[i];
//	prArr(V,3,int);
	n++;
	for(int t = 0;t <= 5*n;t++){
		int i = t%3;
		int & x = P[i];
		x = (x + V[i])%n;
		int me = 1 << i;
		int seen = (vis[x] & ~me);
		if(x && seen) {
			cout << t + 1 << endl;
			return 0;
		}
		vis[x] |= me;
	}
	cout << "3000000000" << endl;
	return 0;
}
#endif
