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

const int MAX = 111;
string S[MAX];
int W[MAX],ord[MAX],n,m;
char buffer[1 << 20];


int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	tc(){
		scanf("%d %d",&n,&m);
		loop(i,n){
			scanf("%s %d",buffer,W + i);
			S[i] = string(buffer);
			ord[i] = i;
		}
		sort(ord,ord + n,[](const int & a,const int & b){
			if(W[a] != W[b]) return W[a] > W[b];
			return S[a] < S[b];
		});
		ll ans = 0;
		loop(j,m) {
			int i = ord[j];
			ans += (m-j)*(ll) W[i];
		}
		printf("%lld",ans);
		loop(j,m){
			int i = ord[j];
			printf(" %s",S[i].c_str());
		}
		puts("");
	}
	return 0;
}
#endif
