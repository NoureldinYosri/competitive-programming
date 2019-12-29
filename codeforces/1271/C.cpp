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

const int MAXN = 200*1000 + 10;
pi O;
pi P[MAXN];
int n;
int dx[] = {-1,0,1,0};
int dy[] = {0,1,0,-1};

ll dist(pi A,pi B){
	return abs(A.first - (ll)B.first) + abs(A.second - (ll)B.second);
}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	scanf("%d %d %d",&n,&O.first,&O.second);
	loop(i,n) scanf("%d %d",&P[i].first,&P[i].second);
	pair<int,pi> ans(0,pi(O.first + 1,O.second));
	
	loop(k,4){
		pi q (O.first + dx[k], O.second + dy[k]);
		int tmp = 0;
		loop(i,n) tmp += dist(O,q) + dist(q,P[i]) == dist(O,P[i]);
		ans = max(ans,pair<int,pi>(tmp,q));
	}
	printf("%d\n%d %d\n",ans.first,ans.second.first, ans.second.second);
	return 0;
}
