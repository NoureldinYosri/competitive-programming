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

const int MAX = 150000 + 10, MAXST = 1 << 20, oo = 1 << 29;
int n, m, H;
int A[MAX], B[MAX];
pi ST[MAXST];

void build(int cur, int s, int e){
	ST[cur] = pi(oo, 0);
	if(s == e) return;
	int m = (s + e) >> 1, left = 2*cur + 1, right = left + 1;
	build(left, s, m);
	build(right, m+1, e);
}

void update(int cur, int s, int e, int p, int v){
	if(s == e) {
		ST[cur].second += v;
		if(ST[cur].second) 
			ST[cur].first = s - ST[cur].second;
		else 
			ST[cur].first = oo;
//		cerr << "@" << s << " " << ST[cur] << endl;
		return;
	}
	int m = (s + e) >> 1, left = 2*cur + 1, right = left + 1;
	
	if(p <= m) update(left, s, m, p, v);
	else update(right, m+1, e, p, v);
	
	ST[cur].second = ST[left].second + ST[right].second;
	ST[cur].first = min(ST[left].first, ST[right].first - ST[left].second);
}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	scanf("%d %d %d", &n, &m, &H);
	loop(i, m) {
		scanf("%d", B + i);
		B[i] = H - B[i];
	}
	sort(B, B + m);
	loop(i, n){
		scanf("%d", A + i);
		A[i] = upper_bound(B, B + m, A[i]) - B;
	}
//	prArr(B, m, int);
//	prArr(A, n, int);
	build(0, 0, m);
	loop(i, m-1) update(0, 0, m, A[i], 1);
	int ans = 0;
	for(int i = m-1; i < n; i++){
		update(0, 0, m, A[i], 1);
		ans += ST[0].first >= 0;
		update(0, 0, m, A[i-m+1], -1);
	}
	cout << ans << endl;
	return 0;
}
