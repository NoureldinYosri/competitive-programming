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


const int MAX = 200*1000 + 10;
char S[MAX];
int n, m;
vi pL, pR;
vi sL, sR;
vi X;

void tc(){
	scanf("%d %d", &n, &m);
	scanf("%s", S);
	pL.clear();
	sL.clear();
	pR.clear();
	sR.clear();
	X.clear();
	
	for(int i = 0, x = 0, mn = 0, mx = 0; i < n; i++){
		pL.push_back(mn);
		pR.push_back(mx);
		X.push_back(x);
		if(S[i] == '+') x++;
		else x--;
		mn = min(mn, x);
		mx = max(mx, x);		
	}
	for(int i = n-1, x = 0, y = 0; i >= 0; i--){
		sL.push_back(y);
		sR.push_back(x);
		if(S[i] == '+'){
			x++;
			y++;
			x = max(x, 1);
		} else {
			x--;
			y--;
			y = min(y, -1);
		}
	}
	reverse(all(sL));
	reverse(all(sR));
	while(m--){
		int s, e; scanf("%d %d", &s, &e);
		s--, e--;
		int l = min(pL[s], X[s] + sL[e]);
		int r = max(pR[s], X[s] + sR[e]);
		printf("%d\n", r-l+1);
	}
}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	int T; scanf("%d", &T);
	while(T--) tc();
	return 0;
}
