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

const int MAX = 10*1000;
int X[MAX],Y[MAX],n;
pi P[MAX];

ll cross(pi a,pi b,pi c) {
	b.first -= a.first,b.second -= a.second;
	c.first -= a.first,c.second -= a.second;
	return b.first*(ll)c.second - b.second*(ll)c.first;
}

vi ord;
pi solve(pi A,pi B) {
	pi ret(0,0);
	loop(j,n) {
		int i = ord[j];
		ll s = cross(A,B,P[i]);
//		cout << A << " " << B << " " << P[i] << ": " << s << endl;
		if(s == 0) continue;
		if(s > 0) ret.first = i+1;
		else ret.second = i+1;
		if(ret.first && ret.second) return ret;
	}
	return ret;
}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	scanf("%d",&n);
	loop(i,n){
		scanf("%d %d",X + i,Y + i);
		P[i] = pi(X[i],Y[i]);
		ord.push_back(i);
	}
	int m; scanf("%d",&m);
	pi A,B;
	random_shuffle(all(ord));
	loop(i,m) {
		scanf("%d %d",&A.first,&A.second);
		scanf("%d %d",&B.first,&B.second);
		pi res = solve(A,B);
		if(!res.first || !res.second) puts("0");
		else printf("%d %d\n",res.first,res.second);
	}
	return 0;
}
#endif
