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

const int MAX = 100*1000 + 10;

pi A[MAX][3],B[MAX][3];
int n,m;
int parity[MAX];

vector<pair<pi,pi>> getEdges(pi T[MAX][3],int n) {
	map<pair<pi,ll>,vector<pair<pi,int>>> lines;
	vector<pair<pi,pi>> ret;
	loop(i,n){
//		loop(j,3) cout << "\t" << T[i][j] << " ";
//		cout << endl;
		loop(j,3) {
			pi a = T[i][j],b = T[i][(j+1)%3];
			if(a > b) swap(a,b);
			ll dy = b.second - a.second,dx = b.first - a.first;
			// (y - a.y)/(x - a.x) = dy/dx
			int A = dx;
			int B = -dy;
			ll C = -dx*a.second + a.first*dy;
//			cout << a << " " << b << " -> ";
//			cout << A << " " << B << " " << C << endl;
			ll g = __gcd(__gcd(abs(A) + 0LL,abs(B)+0LL),abs(C));
			A /= g,B /= g,C /= g;
			if(A < 0) A *= -1,B *= -1,C *= -1;
			else if(A == 0) {
				if(B < 0) B *= -1,C *= -1;
				else if(B == 0) {
					if(C < 0) C *= -1;
				}
			}
			auto line = mp(pi(A,B),C);
			lines[line].emplace_back(a,i);
			lines[line].emplace_back(b,i);
		}
	}
	for(auto pq : lines) {
		auto pnts = pq.second;
		sort(all(pnts));
		int ctr = 0;
		pi prv;
		vector<pair<pi,pi>> aux;
		for(auto p_i : pnts) {
			pi p = p_i.first;
			int i = p_i.second;
//			cout << p_i << " ";
			if(p != prv && ctr == 1) {
				if(aux.empty() || aux.back().second.first < prv.first)
					aux.emplace_back(prv,p);
				else
					aux.back().second = p;
			}
			ctr += 1-2*parity[i];
			parity[i] ^= 1;
			prv = p;
		}
		for(auto q : aux) ret.emplace_back(q);
//		cout << endl;
	}
	sort(all(ret));
	return ret;
}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	scanf("%d",&n);
	loop(i,n) loop(j,3) scanf("%d %d",&A[i][j].first,&A[i][j].second);
	scanf("%d",&m);
	loop(i,m) loop(j,3) scanf("%d %d",&B[i][j].first,&B[i][j].second);
	vector<pair<pi,pi>> E1 = getEdges(A,n);
	vector<pair<pi,pi>> E2 = getEdges(B,m);
	puts((E1 == E2) ? "yes" : "no");
	return 0;
}
