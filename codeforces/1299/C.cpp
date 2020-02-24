#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define all(A) A.begin(),A.end()
#define pb push_back
#define mp make_pair
#define sz(A) ((int)A.size())
typedef std::vector<int> vi;
typedef std::pair<long long, long long> pi;
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

const int MAXLG = 20;
double A[1 << 20];
int n, B[1 << 20];
ll S[1 << 20];
pi P[1 << 20];
vi ord;
bool active[1 << 20];
int nxt[1 << 20];


ll cross(pi a, pi b, pi c){
	b.first -= a.first, b.second -= a.second;
	c.first -= a.first, c.second -= a.second;
	return b.first*(ll)c.second - b.second*(ll)c.first;
}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	scanf("%d",&n);
	loop(i, n) scanf("%d", B + i + 1), S[i+1] = S[i] + B[i+1];
	loop(i, n+1) P[i] = pi(i, S[i]), ord.pb(i);
	sort(all(ord), [](const int & a, const int & b){
		return P[a] > P[b];
	});
	
	vi H;
	for(int i : ord){
		while(sz(H) > 1 && cross(P[H[sz(H)-2]], P[H.back()], P[i]) >= 0) H.pop_back();
		H.pb(i);
	}
	for(int i : H) {
		active[i] = 1;
		//cout << P[i] << endl;
	}
	
	nxt[n+1] = n;
	for(int i = n;i >= 1;i--){
		if(active[i]) nxt[i] = i;
		else nxt[i] = nxt[i+1];
	}
	
	for(int i = 1;i <= n;){
		int j = nxt[i];
		double s = S[j] - S[i-1];
		s /= j-i+1;
		for(;i <= j;i++)
			A[i] = s;
	}
	for(int i = 1;i <= n;i++)
		printf("%.8f\n", A[i]);
	
	return 0;
}
