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


vi getBest(vi A) {
	vi ret = A;
	for(int i = 0;i < sz(A);i++) {
		rotate(A.begin(),A.begin() + 1,A.end());
		ret = min(ret,A);
	}
	return ret;
}

vi f(vp V) {
	vi A;
	A.push_back(V[1].first);
	A.push_back(V[2].first);
	A.push_back(V[1].second);
	A.push_back(V[2].second);
	vi f,g;
	f.push_back(V[0].first);
	f.push_back(V[0].second);
	for(int x : getBest(A)) f.push_back(x);
	g.push_back(V[0].second);
	g.push_back(V[0].first);
	reverse(all(A));
	for(int x : getBest(A)) g.push_back(x);
	return min(f,g);
}


vi canonize(vector<pi> V) {
	vi canon;
	for(int i = 0;i < 3;i++) {
		vp Q;
		Q.push_back(V[i]);
		loop(k,2) Q.push_back(V[(i+k+1)%3]);
		vi tmp = f(Q);
		if(canon.empty() || tmp < canon) canon = tmp;
	}
//	print(canon,int);
	return canon;
}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	map<vi,int> mem;
	vp V;
	int n; scanf("%d",&n);
	loop(i,n) {
		V.clear();
		loop(j,3) {
			pi p; scanf("%d %d",&p.first,&p.second);
			V.push_back(p);
		}
		mem[canonize(V)]++;
	}
	int ans = 0;
	for(auto p : mem) ans = max(ans,p.second);
	cout << ans << endl;
	return 0;
}
#endif
