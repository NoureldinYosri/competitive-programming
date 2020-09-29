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

const int MAXB = 20;
set<pi> M;
int n;
vi S[MAXB];
int A[1 << 20];

void insert(int i, int x){
	M.emplace(x, i);
	loop(b, MAXB) if((x >> b) & 1) S[b].pb(i);
}




int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	scanf("%d", &n);
	loop(i, n) {
		int x; scanf("%d", &x);
		insert(i, x);
		A[i] = x;
	}
	ll ans = 0;
	while(!M.empty()){
		auto [cx, ci] = *M.rbegin();
		M.erase(*M.rbegin());
		A[ci] = 0;
		
		for(int b = MAXB-1; b >= 0; b--){
			int have = (cx >> b) & 1;
			if(have) continue;
			while(!S[b].empty()){
				int i = S[b].back(); 
				if((A[i] >> b)&1) break;
				S[b].pop_back();
			}
			if(S[b].empty()) continue;
			int i = S[b].back();
			int y = A[i];
			M.erase(pi(y, i));
			A[i] &= cx;
			M.insert(pi(A[i], i));
			cx |= y;
		}
		ans += cx*(ll)cx;
	}
	
	cout << ans << endl;
	return 0;
}
