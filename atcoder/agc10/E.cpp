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

const int MAX = 2 << 10;
int pos[MAX],blocker[MAX];
bool friends[MAX][MAX];
int A[MAX],n;
bool used[MAX];
bitset<MAX> BS[MAX];



int insert(int i,vi & V) {
	static vi aux;
	aux.clear();
	used[i] = 1;
	while(!V.empty() && friends[i][V.back()]) {
		aux.push_back(V.back());
		V.pop_back();
	}
	int r = V.size();
	V.push_back(i);
	while(!aux.empty()) {
		int y = aux.back();
		pos[y] = V.size();
		V.push_back(y);
		aux.pop_back();
	}
	return r;
}

int main(){
#ifdef HOME
//	freopen("in.in","r",stdin);
	freopen("1.in", "r", stdin);
	freopen("out.out","w",stdout);
#endif
	scanf("%d",&n);
	loop(i,n) scanf("%d",A + i);
	sort(A,A + n);
	loop(i,n) loop(j,n) {
		friends[i][j] = __gcd(A[i],A[j]) == 1;
		if(friends[i][j] != 1) BS[i].set(j);
	}
	loop(i,n) blocker[i] = -1;

	vi res,cand;
	bitset<MAX> aux,inRes;
	for(int t = 0;t < n;t++) {
		int best = -1;
		cand.clear();
		for(int i = 0;i < n;i++) if(!used[i]) {
			int b = blocker[i],pot = 0;
			if(b != -1) pot = pos[b] + 1;
			if(pot > best) {
				best = pot;
				cand.clear();
			}
			if(best == pot)cand.push_back(i);
		}
//		if(!t) {
//			print(cand,int);
//		}
		int ci = sz(cand) - 1;
		aux.reset();
		aux |= BS[cand.back()];
		for(int i = sz(cand)-2;i >= 0;i--) {
			aux &= ~inRes;
			auto tmp = BS[cand[i]] & ~inRes;
			bool y = 1;
			for(int j = i+1;j < sz(cand) && y;j++)
				y &= (tmp & (BS[j] & ~inRes)).count();
			if(y) ci = i;
		}
		ci = cand[ci];
//		if(!t) cerr << ci << " " << A[ci] << " " << aux << endl;
		inRes.set(ci);
		res.push_back(ci);
		int k = sz(res);
//		int k = insert(ci,res) + 1;
		for(int i = 0;i < n;i++) if(!used[i] && !friends[ci][i]) {
			int b = blocker[i],pot = 0;
			if(b != -1) pot = pos[b] + 1;
			if(k > pot) blocker[i] = ci;
		}
//		cerr << A[ci] << endl;
	}
	for(int i = 0;i < n;i++) printf("%d%c",A[res[i]]," \n"[i==n-1]);
	return 0;
}
