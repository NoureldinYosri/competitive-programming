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


pi P,Q;


ll cross(pi o,pi a,pi b) {
	a.first -= o.first,a.second -= o.second;
	b.first -= o.first,b.second -= o.second;
	return a.first*(ll)b.second - a.second*(ll)b.first;
}




pi readPoint(){
	int x,y; scanf("%d %d",&x,&y);
	return pi(x,y);
}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	vector<pi> U,D;
	int T; scanf("%d",&T);
	for(int t = 1;t <= T;t++) {
		P = readPoint();
		Q = readPoint();
		int n; scanf("%d",&n);
		U.clear(),D.clear();
		for(int i = 0;i < n;i++){
			pi p = readPoint();
			if(cross(P,Q,p) > 0) U.push_back(p);
			else D.push_back(p);
		}
		pair<>
		printf("")
	}
	return 0;
}
