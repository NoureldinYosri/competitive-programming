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

const int MAX = 10000 + 10;
pair<pi,int> P[MAX];
int n;

ll cross(pi o,pi a,pi b) {
	a.first -= o.first,a.second -= o.second;
	b.first -= o.first,b.second -= o.second;
	return a.first*(ll)b.second - a.second*(ll)b.first;
}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	while(scanf("%d",&n) == 1){
		loop(i,n) scanf("%d %d",&P[i].first.second,&P[i].first.first),P[i].second=i;
		int c = min_element(P,P + n) - P;
		if(c) swap(P[0],P[c]);
		loop(i,n) swap(P[i].first.first,P[i].first.second);
		sort(P + 1,P + n,[](const pair<pi,int> & a,const pair<pi,int> & b) {
			return cross(P[0].first,a.first,b.first) > 0;
		});
		int a = P[0].second+1,b = P[n/2].second + 1;
		if(a > b) swap(a,b);
		printf("%d %d\n",a,b);
	}
	return 0;
}
#endif
