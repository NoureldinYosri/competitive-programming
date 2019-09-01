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


int change[25][3],n;
struct cmp{
	ll operator () (const pi & a) const {
		return a.first * 1e9 + a.second;
	}
};

void getScores(int aux,int s,int m,vi & scores,bool verbose = 0) {
	static string name = "LMW";
	loop(i,m) {
		int ignore = aux%3; aux /= 3;
		int a = ignore ? 0 : 1;
		int b = 3 - a - ignore;
		scores[a] += change[i + s][a];
		scores[b] += change[i + s][b];
		if(verbose) printf("%c%c\n",name[a],name[b]);
	}
}

using table = unordered_map<pi,pi,cmp>;
table bf(int s,int m) {
	int tot = 1;
	loop(i,m) tot *= 3;
	table M;
	for(int msk = 0;msk < tot;msk++) {
		vi scores(3,0);
		getScores(msk,s,m,scores);
		pi h(scores[1] - scores[0],scores[2] - scores[1]);
		if(!M.count(h)) M[h] = pi(INT_MIN,0);
		M[h] = max(M[h],pi(scores[0],msk));
//		cerr << h << ": ";
//		print(scores,int);
	}
//	cerr << string(30,'*') << endl;
	return M;
}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	scanf("%d",&n);
	loop(i,n) loop(j,3) scanf("%d",change[i] + j);
	int m = n/2;
	auto A = bf(0,m);
	auto B = bf(m,n-m);
	int offset = 1;
	loop(i,m) offset *= 3;
	pair<int,pi> ans(INT_MIN,pi(0,0));
	bool f = 0;
	for(auto pq : A) {
		auto p = pq.first;
		auto q = pq.second;
		pi other(-p.first,-p.second);
		auto ptr = B.find(other);
		if(ptr != B.end()) {
//			cerr << p << " " << ptr->first << ": " << q << " " << ptr->second << endl;
			f = 1;
			pi t = ptr->second;
			int s = q.first + t.first;
			ans = max(ans,make_pair(s,pi(q.second,t.second)));
		}
	}
	if(!f) puts("Impossible");
	else {
		string name = "LMW";
		vi scores(3,0);
		getScores(ans.second.first,0,m,scores,1);
		getScores(ans.second.second,m,n-m,scores,1);
//		cerr << ans.first << endl;
//		print(scores,int);
//		assert(ans.first == scores[0]);
	}
	return 0;
}

/*
 * 6 9 -2 -> 3, -11
 * -1 -4 7 -> -3, 11
 * 5 5 5
 */
