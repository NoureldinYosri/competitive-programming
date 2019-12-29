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


int n,m;

set<int> forbidden;
queue<pair<int,pi> > cand;

vi pos;
ll ans = 0;

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	scanf ("%d %d",&n,&m);
	for(int i = 0;i < n;i++){
		int x; scanf("%d",&x);
		forbidden.insert(x);
		for(int dx = -1;dx <= 1; dx += 2)
			cand.emplace(1, pi(x + dx, dx));
	}
	for(int i = 0;i < m;i++){
		while(1){
			auto tmp = cand.front();
			int x = tmp.second.first;
			if(forbidden.count(x)){
				cand.pop();
			}
			else break;
		}
		auto tmp = cand.front();
		cand.pop();
		int d = tmp.first;
		int x = tmp.second.first;
		pos.push_back(x);
		forbidden.insert(x);
		int dx = tmp.second.second;
		ans += d;
		cand.emplace(d + 1, pi(x + dx, dx));
	}
	printf("%lld\n",ans);
	for(int x : pos) printf("%d ",x);
	return 0;
}
