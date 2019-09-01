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


const int MAX = 200*1000 + 10,MAXB = 500;
int A[MAX],n;
int flag[MAX],m;
int Q;

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	scanf("%d",&n);
	loop(i,n) scanf("%d",A + i);
	int B = sqrt(n) + 2;
	m = (n - 1)/B + 1;
	scanf("%d",&Q);
	while(Q--) {
		int t; scanf("%d",&t);
		if(t == 1){
			int p,x; scanf("%d %d",&p,&x);
			p--;
			int u = p/B;
			int s = u*B,e = min(s + B,n);
			for(int i = s;i < e;i++) A[i] = max(A[i],flag[u]);
			A[p] = x;
			flag[u] = 0;
		}
		else {
			int x; scanf("%d",&x);
			for(int u = 0;u < m;u++)
				flag[u] = max(flag[u],x);
		}
	}
	loop(i,n) printf("%d%c",max(A[i],flag[i/B])," \n"[i==n-1]);
	return 0;
}
#endif
